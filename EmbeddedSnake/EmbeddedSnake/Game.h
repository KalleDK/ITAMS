#ifndef GAME_H_
#define GAME_H_

#include "snakeio.h"

template<typename BUFFER, uint8_t HEIGHT, uint8_t WIDTH>
class Game
{
public:
	enum class SnakeDirection : int8_t
	{
		SnakeUp		= -28,
		SnakeDown	= +28,
		SnakeLeft	= -1,
		SnakeRight	= +1,
	};
	
	Game(BUFFER* buffer) : buffer_(buffer)
	{
		for (uint8_t i = 0; i < width_; ++i)
		{
			screen[i] = properties::Border;
			screen[i + (width_ * (height_ - 1))] = properties::Border;
		}
		
		for(uint8_t i = 0; i < height_; ++i)
		{
			screen[i * width_] = properties::Border;
			screen[(i * width_) + (width_ - 1)] = properties::Border;
		}
		
		screen[(4 * width_) + 5] = properties::Fruit;
		
		fruit_ = (4 * width_) + 5;
		head_ = (8 * width_) + 14;
		tail_ = (8 * width_) + 15;
		
		screen[head_] = (properties) ((uint8_t) properties::Snake | (uint8_t) properties::SnakeLeft);	
		screen[tail_] = (properties) ((uint8_t) properties::Snake | (uint8_t) properties::SnakeLeft);	
		
		lastDirection_ = SnakeDirection::SnakeLeft;
		
		drawFruit();
		AddHeadToScreenBuffer();
		buffer_->draw_border(Point{2,2},80,44,1);
		buffer_->update();
	}
	
	void GameTick(SnakeController* nes)
	{
		switch (nes->Direction)
		{
		case Up:
			MoveSnake(SnakeDirection::SnakeUp);
			break;
		case Down:
			MoveSnake(SnakeDirection::SnakeDown);
			break;
		case Left:
			MoveSnake(SnakeDirection::SnakeLeft);
			break;
		case Right:
			MoveSnake(SnakeDirection::SnakeRight);
			break;
		case None:
			MoveSnake(lastDirection_);
			break;
		}
	}
	
	void MoveSnake(SnakeDirection direction)
	{
		if((static_cast<int8_t>(direction) + static_cast<int8_t>(lastDirection_)) == 0)
		{
			direction = lastDirection_;
		}
		
		uint16_t nextField = head_ + static_cast<int8_t>(direction);
		
		if(!!((uint8_t)screen[nextField] & (static_cast<uint8_t>(properties::Border) | (uint8_t) properties::Snake)))
		{
			InitiateDeathSequence();
		}
		else
		{
			if((uint8_t)screen[nextField] & (uint8_t)properties::Fruit)
			{
				//DO not delete tail
				score_++;
				uint8_t da = 3;

				do 
				{
					++da;
					fruit_ = (((head_ % tail_) - ((head_ % tail_)*da) +da) % 448);
				} while (((uint8_t)screen[fruit_] & ((uint8_t)properties::Snake | (uint8_t)properties::Border)));
				screen[fruit_] = properties::Fruit;
				drawFruit();
			}
			else
			{
				//Delete tail
				RemoveTailFromScreenBuffer();
				
				properties old = screen[tail_];
				screen[tail_] = properties::None;
				
				switch(((properties)((uint8_t)old & 0xF0)))
				{
				case properties::SnakeUp:
					tail_ += (int8_t)SnakeDirection::SnakeUp;
					break;
				case properties::SnakeDown:
					tail_ += (int8_t)SnakeDirection::SnakeDown;
					break;
				case properties::SnakeLeft:
					tail_ += (int8_t)SnakeDirection::SnakeLeft;
					break;
				case properties::SnakeRight:
					tail_ += (int8_t)SnakeDirection::SnakeRight;
					break;
				default:
				break;
				}
			}
			
			//NOT DEAD GRINGO YOU GOTTA MOVE!!

			switch(direction)
			{
				case SnakeDirection::SnakeUp:
				screen[head_] = (properties)((uint8_t)screen[head_] | (uint8_t)properties::SnakeUp);
				break;
				case SnakeDirection::SnakeDown:
				screen[head_] = (properties)((uint8_t)screen[head_] | (uint8_t)properties::SnakeDown);
				break;
				case SnakeDirection::SnakeLeft:
				screen[head_] = (properties)((uint8_t)screen[head_] | (uint8_t)properties::SnakeLeft);
				break;
				case SnakeDirection::SnakeRight:
				screen[head_] = (properties)((uint8_t)screen[head_] | (uint8_t)properties::SnakeRight);
				break;
			}
			
			lastDirection_ = direction;
			head_ = nextField;
			
			screen[nextField] = properties::Snake;
			
			AddHeadToScreenBuffer();
			DrawScreen();
		}
	}
	
	void DrawScreen()
	{
		buffer_->update();
	}
	
	void AddHeadToScreenBuffer() 
	{
		buffer_->draw_square(Point { (int16_t)((head_ % width_) * 3), (int16_t)((head_ / width_) * 3) }, 3, 3);
	}
	
	void RemoveTailFromScreenBuffer()
	{
		buffer_->clear_square(Point { (int16_t)((tail_ % width_) * 3), (int16_t)((tail_ / width_) * 3) }, 3, 3);
	}
	
	void drawFruit()
	{
		buffer_->draw_square(Point { (int16_t)((fruit_ % width_) * 3)+1, (int16_t)((fruit_ / width_) * 3) }, 1, 1);
		buffer_->draw_square(Point { (int16_t)((fruit_ % width_) * 3), (int16_t)((fruit_ / width_) * 3)+1 }, 1, 1);
		buffer_->draw_square(Point { (int16_t)((fruit_ % width_) * 3)+1, (int16_t)((fruit_ / width_) * 3)+2 }, 1, 1);
		buffer_->draw_square(Point { (int16_t)((fruit_ % width_) * 3)+2, (int16_t)((fruit_ / width_) * 3)+1 }, 1, 1);		
	}
	
	void InitiateDeathSequence()
	{
		// GAME OVER, MATEY!
		// printf(score_);
	}
	
private:
	uint16_t head_;
	uint16_t tail_;
	uint16_t fruit_;

	SnakeDirection lastDirection_;
	
	uint8_t score_ = 0;
	
	enum class properties : uint8_t
	{
		None		= 0,
		Snake		= (1<<0),
		Border		= (1<<1),
		Fruit		= (1<<2),
		Unknown		= (1<<3),
		SnakeUp		= (1<<4),
		SnakeDown	= (1<<5),
		SnakeLeft	= (1<<6),
		SnakeRight	= (1<<7),

	};

	static const uint8_t height_ = HEIGHT;
	static const uint8_t width_ = WIDTH;

	properties screen[height_ * width_] = {};
		
	BUFFER* buffer_;
};



#endif /* GAME_H_ */