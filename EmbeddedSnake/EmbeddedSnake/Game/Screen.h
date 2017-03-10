/*
 * Screen.h
 *
 * Created: 3/9/2017 1:03:23 PM
 *  Author: live
 */ 


#ifndef GAME_SCREEN_H_
#define GAME_SCREEN_H_

#include "Point.h"
#include "Enums.h"

namespace Game {
	
	static const uint8_t textEncodeding[5*43] = {
			//0
			0b00111100,
			0b01000010,
			0b01011010,
			0b01000010,
			0b00111100,
			//1
			0b01111111,
			0b00000010,
			0b00000100,
			0b00001000,
			0b00000000,
			//2
			0b01000110,
			0b01001001,
			0b01010001,
			0b01100001,
			0b01100110,
			//3
			0b00110110,
			0b01001001,
			0b01001001,
			0b01000001,
			0b00100010,
			//4
			0b01111111,
			0b00010001,
			0b00010010,
			0b00010100,
			0b00011000,
			//5
			0b00110001,
			0b01001001,
			0b01001001,
			0b01001001,
			0b00101111,
			//6
			0b00110010,
			0b01001001,
			0b01001001,
			0b01001001,
			0b00111110,
			//7
			0b00000111,
			0b00011001,
			0b01100001,
			0b00000001,
			0b00000001,
			//8
			0b00110110,
			0b01001001,
			0b01001001,
			0b01001001,
			0b00110110,
			//9
			0b00111110,
			0b01001001,
			0b01001001,
			0b01001001,
			0b00100110,
			//:
			0b00000000,
			0b00000000,
			0b00100100,
			0b00000000,
			0b00000000,
			//;
			0b00000000,
			0b00000000,
			0b00100100,
			0b01000000,
			0b00000000,
			//<
			0b01000010,
			0b01000010,
			0b01000010,
			0b00100100,
			0b00011000,
			//=
			0b00000000,
			0b00100100,
			0b00100100,
			0b00100100,
			0b00000000,
			//>
			0b00011000,
			0b00100100,
			0b00100100,
			0b01000010,
			0b01000010,
			//?
			0b00000110,
			0b00001001,
			0b01110001,
			0b00000001,
			0b00000010,
			//@
			0b00011110,
			0b10101001,
			0b10111101,
			0b10000001,
			0b01111110,
			//A
			0b00111110,
			0b01001000,
			0b10001000,
			0b01001000,
			0b00111110,
			//B
			0b00110110,
			0b01001001,
			0b01001001,
			0b01001001,
			0b01111111,
			//C
			0b00100010,
			0b01000001,
			0b01000001,
			0b01000001,
			0b00111110,
			//D
			0b00111110,
			0b01000001,
			0b01000001,
			0b01000001,
			0b01111111,
			//E
			0b01000001,
			0b01001001,
			0b01001001,
			0b01001001,
			0b01111111,
			//F
			0b00000001,
			0b00001001,
			0b00001001,
			0b00001001,
			0b01111111,
			//G
			0b00110010,
			0b01010001,
			0b01010001,
			0b01000001,
			0b00111110,
			//H
			0b01111111,
			0b00001000,
			0b00001000,
			0b00001000,
			0b01111111,
			//I
			0b01000001,
			0b01000001,
			0b01111111,
			0b01000001,
			0b01000001,
			//J
			0b00111111,
			0b01000000,
			0b01000000,
			0b01000000,
			0b00110000,
			//K
			0b01000001,
			0b00100010,
			0b00010100,
			0b00011000,
			0b01111111,
			//L
			0b01000000,
			0b01000000,
			0b01000000,
			0b01000000,
			0b01111111,
			//M
			0b01111111,
			0b00000010,
			0b00000100,
			0b00000010,
			0b01111111,
			//N
			0b01111111,
			0b01100000,
			0b00011000,
			0b00000110,
			0b01111111,
			//O
			0b00111110,
			0b01000001,
			0b01000001,
			0b01000001,
			0b00111110,
			//P
			0b00000110,
			0b00001001,
			0b00001001,
			0b00001001,
			0b01111111,
			//Q
			0b01111110,
			0b01100001,
			0b01010001,
			0b01000001,
			0b00111110,
			//R
			0b01000110,
			0b00101001,
			0b00011001,
			0b00001001,
			0b01111111,
			//S
			0b01100110,
			0b01010001,
			0b01001001,
			0b01001001,
			0b01100110,
			//T
			0b00000001,
			0b00000001,
			0b01111111,
			0b00000001,
			0b00000001,
			//U
			0b00111111,
			0b01000000,
			0b01000000,
			0b01000000,
			0b00111111,
			//V
			0b00011111,
			0b00100000,
			0b01000000,
			0b00100000,
			0b00011111,
			//W
			0b01111111,
			0b00100000,
			0b01000000,
			0b00100000,
			0b01111111,
			//X
			0b01100011,
			0b00010100,
			0b00001000,
			0b00010100,
			0b01100011,
			//Y
			0b00000111,
			0b00001000,
			0b01110000,
			0b00001000,
			0b00000111,
			//Z
			0b01000011,
			0b01000101,
			0b01001001,
			0b01110001,
			0b01100001,
		};
	
	template<typename BUFFER>
	struct Screen {
		
		using buffer_type     = BUFFER;
		using buffer_type_ptr = buffer_type*;
		
		using buffer_point_type     = typename buffer_type::point_type;
		using buffer_point_type_ptr = typename buffer_type::point_type_ptr;
		
		using point_type      = Point;
		using point_type_ptr  = Point*;
		
		buffer_type_ptr buffer_;
		
		Screen(buffer_type_ptr buffer) : buffer_(buffer) {};
			
		buffer_point_type convert_point(const point_type& point) const {
			return buffer_point_type{point.x * 4 - 2, point.y * 4 - 2};
		}
		
		void init() {
			buffer_->init();
		}
			
		void clear() {
			buffer_->clear();
		}
			
		void update() {
			buffer_->update();
		}
			
		
		void draw_idle_menu() {
			buffer_->draw_square_with_border(buffer_point_type{4, 6}, 8*6, 12, 1);
			
			WriteText(6,1, "PAUSE");
		}
		
		template<typename T>
		void draw_win_menu(T score) {
			buffer_->draw_square_with_border(buffer_point_type{4, 6}, 8*7, 12, 1);
			
			WriteText(6,1, "YOU WON");

		}
		
		template<typename T>
		void draw_game_over_menu(T score) {
			buffer_->draw_square_with_border(buffer_point_type{4, 6}, 8*8, 24, 1);
			
			WriteText(6,1, "YOU DIED");
			
			uint8_t i = 0;
			do 
			{
				WriteChar(30 - (8*i), 2, (score % 10) + '0');
				score = score / 10;
			} while (score > 0);
			

		}
		
		
		
		void draw_none(const buffer_point_type& point) {
			buffer_->clear_square(buffer_point_type{point.x - 1, point.y - 1}, 5, 5);
		}
		
		void draw_snake(const buffer_point_type& point, snake_value direction) {
			
			switch(direction) {
				case(Direction::Up)    : buffer_->draw_square(buffer_point_type{point.x     , point.y - 1 }, 3     , 3 + 1 ); break;
				case(Direction::Down)  : buffer_->draw_square(buffer_point_type{point.x     , point.y     }, 3     , 3 + 1 ); break;
				case(Direction::Left)  : buffer_->draw_square(buffer_point_type{point.x - 1 , point.y     }, 3 + 1 , 3     ); break;
				case(Direction::Right) : buffer_->draw_square(buffer_point_type{point.x     , point.y     }, 3 + 1 , 3     ); break;
				default: buffer_->draw_square(point, 3, 3); break;
			}
		}
		
		void draw_fruit(const buffer_point_type& point)
		{	
			draw_none(point);
			
			buffer_->draw_square(buffer_point_type { point.x + 1  , point.y     }, 1, 1);
			buffer_->draw_square(buffer_point_type { point.x      , point.y + 1 }, 1, 1);
			buffer_->draw_square(buffer_point_type { point.x + 2  , point.y + 1 }, 1, 1);
			buffer_->draw_square(buffer_point_type { point.x + 1  , point.y + 2 }, 1, 1);
		}
		
		void draw_border(const buffer_point_type& point, border_value direction) {
			switch(direction) {
				case(border_value::North)     : buffer_->draw_square(buffer_point_type{point.x - 1 , point.y + 2 }, 5 , 1 ); break;
				case(border_value::South)     : buffer_->draw_square(buffer_point_type{point.x - 1 , point.y     }, 5 , 1 ); break;
				case(border_value::East)      : buffer_->draw_square(buffer_point_type{point.x     , point.y - 1 }, 1 , 5 ); break;
				case(border_value::West)      : buffer_->draw_square(buffer_point_type{point.x + 2 , point.y - 1 }, 1 , 5 ); break;
				case(border_value::NorthWest) : buffer_->draw_square(buffer_point_type{point.x + 2 , point.y + 2 }, 1 , 1 ); break;
				case(border_value::NorthEast) : buffer_->draw_square(buffer_point_type{point.x     , point.y + 2 }, 1 , 1 ); break;
				case(border_value::SouthWest) : buffer_->draw_square(buffer_point_type{point.x + 2 , point.y     }, 1 , 1 ); break;
				case(border_value::SouthEast) : buffer_->draw_square(buffer_point_type{point.x     , point.y     }, 1 , 1 ); break;
				default: break;
			}
		}
		
		
		void draw_none(const point_type& point)
		{
			draw_none(convert_point(point));
		}
		
		void draw_snake(const point_type& point, snake_value direction) {
			draw_snake(convert_point(point), direction);
		}
		
		void draw_fruit(const point_type& point)
		{
			draw_fruit(convert_point(point));
		}
		
		void draw_border(const point_type& point, border_value direction) {
			draw_border(convert_point(point), direction);
		}
		
		private:
		void WriteChar(const uint8_t& startCol, const uint8_t& startRow, const char letter){

				uint8_t place = ((letter - '0')*5)+4;
				buffer_->set_data(startCol , startRow, textEncodeding[place]);
				buffer_->set_data(startCol + 1, startRow, textEncodeding[place - 1]);
				buffer_->set_data(startCol + 2, startRow, textEncodeding[place - 2]);
				buffer_->set_data(startCol + 3, startRow, textEncodeding[place - 3]);
				buffer_->set_data(startCol + 4, startRow, textEncodeding[place - 4]);
	
		}
		
		void WriteText(const uint8_t& startCol, const uint8_t& startRow, const char* letters){
			uint8_t index = 0;
			while (*letters != '\0')
			{
				if (*letters == ' ');
				{
					letters++;
					index += 6;
					continue;
				}
				uint8_t place = ((*letters - '0')*5)+4;
				buffer_->set_data(startCol + index, startRow, textEncodeding[place]);
				buffer_->set_data(startCol + index + 1, startRow, textEncodeding[place - 1]);
				buffer_->set_data(startCol + index + 2, startRow, textEncodeding[place - 2]);
				buffer_->set_data(startCol + index + 3, startRow, textEncodeding[place - 3]);
				buffer_->set_data(startCol + index + 4, startRow, textEncodeding[place - 4]);
				letters++;
				index +=6;
			}
		}
	};
}




#endif /* GAME_SCREEN_H_ */