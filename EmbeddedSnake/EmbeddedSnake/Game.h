#ifndef GAME_H_
#define GAME_H_

#include "snakeio.h"


using Direction = NESDirection;


enum class type_id : uint8_t
{
	None		= 0,
	Snake		= 1,
	Border		= 2,
	Fruit		= 3
	
};

enum class game_state : uint8_t
{
	Idle     = 0,
	Playing  = 1
};

enum class fruit_value : uint8_t
{
	Banana		= 0,
	Apple    	= 1,
};

using snake_value = Direction;



class Field {
	
	public:
	
	Field() : data(0) {};

	Field(uint8_t data) : data(data) {};

	void set_snake(snake_value value) {
		set(type_id::Snake, static_cast<uint8_t>(value));
	}
	
	snake_value get_snake() {
		return static_cast<snake_value>(get_value());
	}
	
	void set_fruit(fruit_value value) {
		set(type_id::Fruit, static_cast<uint8_t>(value));
	}
	
	fruit_value get_fruit() {
		return static_cast<fruit_value>(get_value());
	}
	
	void set_border() {
		set(type_id::Border, 0);
	}
	
	void set_none() {
		set(type_id::None, 0);
	}
	
	type_id get_id() {
		return static_cast<type_id>(data & 0x0F);
	}
	
	private:

	uint8_t data;
	
	void set(type_id id, uint8_t value) {
		data = value << 4 | static_cast<uint8_t>(id);
	}
	
	uint8_t get_value() {
		return (data & 0xF0) >> 4;
	}
	
};

struct Snake {
	
	Snake() = default;
	
	Snake(Field* field, Direction direction, uint8_t grow) : head(field), tail(field), grow(grow), direction(direction) {};

	Field* head;
	Field* tail;
	
	uint8_t grow;
	
	Direction direction;
	
};

template<uint8_t WIDTH, uint8_t HEIGHT>
class Area {
	
	
	public:
	static const uint8_t height = HEIGHT;
	static const uint8_t width = WIDTH;
	
	using value_type = Field;
	using value_type_ptr = Field*;

	value_type screen[height * width];

	value_type_ptr begin() const {
		return &screen[0];
	}
	
	value_type_ptr end() const {
		return &screen[height*width];
	}
	
	value_type_ptr end() {
		return &screen[height*width];
	}
	
	value_type_ptr begin() {
		return &screen[0];
	}
	
	value_type_ptr get_field(uint8_t x, uint8_t y) {
		return begin() + (y * width) + x;
	}
	
	value_type_ptr get_neighbour(value_type_ptr field, Direction direction) {
		switch(direction) {
			case(Up) : return field - width;
			case(Down) : return field + width;
			case(Left) : return field - 1;
			case(Right) : return field + 1;
			default: return field;
		}
	}
	
	Point get_coordinate(value_type_ptr field) {
		auto x = (field - begin()) % width;
		auto y = (field - begin()) / width;
		return Point{x * 3, y * 3};
	}
	
};

template<typename BUFFER, typename AREA>
class Game
{
	public:

	
	Game(BUFFER* buffer, AREA* area, SnakeController* controller) : buffer_(buffer), area_(area), controller_(controller)
	{
		reset_game();
	}
	
	// Drawing and screen functions
	
	void clear_area() {
		buffer_->clear();
	}
	
	void draw_fruit(Field* field)
	{
		Point p = area_->get_coordinate(field);
		
		buffer_->draw_square(Point { p.x + 1  , p.y     }, 1, 1);
		buffer_->draw_square(Point { p.x      , p.y + 1 }, 1, 1);
		buffer_->draw_square(Point { p.x + 2  , p.y + 1 }, 1, 1);
		buffer_->draw_square(Point { p.x + 1  , p.y + 2 }, 1, 1);
	}
	
	void draw_border() {
		buffer_->draw_border(Point{2,2},80,44,1);
	}
	
	void draw_snake(Field* field) {
		Point p = area_->get_coordinate(field);
		
		buffer_->draw_square(p, 3, 3);
	}
	
	void draw_none(Field* field) {
		Point p = area_->get_coordinate(field);
		
		buffer_->clear_square(p, 3, 3);
	}
	
	void update_screen() {
		buffer_->update();
	}
	
	
	
	// Setting and updating fields -> these should call their own drawing functions if needed
	
	void set_fruit(Field* field, fruit_value value) {
		field->set_fruit(value);
		
		draw_fruit(field);
	}
	
	void set_none(Field* field) {
		field->set_none();
		
		draw_none(field);
	}
	
	void set_border(Field* field) {
		field->set_border();
	}
	
	void set_snake(Field* field, Direction direction) {
		field->set_snake(direction);
		
		draw_snake(field);
	}
	
	void update_snake(Field* field, Direction direction) {
		field->set_snake(direction);
	}
	
	
	
	// Adding items to the game or removing
	
	void add_area() {
		
		for (Field* itr = area_->begin(); itr != area_->end(); ++itr) {
			itr->set_none();
		}
		
		clear_area();
		
	}
	
	void add_border() {
		
		for (uint8_t x = 0; x < area_->width; ++x) {
			set_border(area_->get_field(x, 0));
			set_border(area_->get_field(x, area_->height - 1));
		}
		
		for (uint8_t y = 0; y < area_->height; ++y) {
			set_border(area_->get_field(0, y));
			set_border(area_->get_field(area_->width - 1, y));
		}
		
		draw_border();
	}
	
	void add_fruit(uint8_t x, uint8_t y, fruit_value value) {
		
		fruit_ = area_->get_field(x,y);
		
		set_fruit(fruit_, value);
	}
	
	void add_snake(uint8_t x, uint8_t y, Direction direction, uint8_t size) {
		snake_ = Snake(area_->get_field(x,y), direction, size);
		
		set_snake(snake_.head, Direction::None);
	}
	

	// Snake functions

	void kill_snake() {};

	void move_snake_tail() {
		// Move tail
		Field* old_tail = snake_.tail;
		
		Direction tail_direction = snake_.tail->get_snake();
		snake_.tail = area_->get_neighbour(snake_.tail, tail_direction);
		
		set_none(old_tail);
		
	}

	void move_snake_head(Field* field) {
		// Update old head with direction
		update_snake(snake_.head, snake_.direction);
		
		// Create new head
		set_snake(field, Direction::None);
		snake_.head = field;
	}


	// Game functions
	void reset_game() {
		add_area();
		add_border();
		add_fruit(5, 4, fruit_value::Apple);
		add_snake(14, 8, Direction::Right, 3);
		
		update_screen();
		
		state_ = game_state::Idle;
	}
	
	
	
	
	// Movement
	
	void move_snake(Direction direction) {
		// Continue if none is pressed
		direction = (direction != Direction::None ? direction : snake_.direction);
		
		// Reversed direction is not allowed
		direction = ((direction == Direction::Right) && (snake_.direction == Direction::Left) ? snake_.direction : direction);
		direction = ((direction == Direction::Left) && (snake_.direction == Direction::Right) ? snake_.direction : direction);
		direction = ((direction == Direction::Up) && (snake_.direction == Direction::Down) ? snake_.direction : direction);
		direction = ((direction == Direction::Down) && (snake_.direction == Direction::Up) ? snake_.direction : direction);
		
		snake_.direction = direction;
		
		Field* field = area_->get_neighbour(snake_.head, direction);
		
		switch(field->get_id()) {
			case(type_id::Border) : move_snake_into_border(field); break;
			case(type_id::Snake) : move_snake_into_snake(field); break;
			case(type_id::None) : move_snake_into_none(field); break;
			case(type_id::Fruit) : move_snake_into_fruit(field); break;
		}
		
	}
	
	void move_snake_into_border(Field* field) {
		kill_snake();
	}
	
	void move_snake_into_snake(Field* field) {
		if ((field == snake_.tail) && (snake_.grow == 0) ) {
			move_snake_into_none(field);
			} else {
			kill_snake();
		}
	}
	
	void move_snake_into_none(Field* field) {
		
		if (snake_.grow == 0) {
			move_snake_tail();
			} else {
			--snake_.grow;
		}
		
		move_snake_head(field);
		
	}
	
	void move_snake_into_fruit(Field* field) {
		++snake_.grow;
		++score_;
		
		fruit_ = snake_.tail + (snake_.head-area_->begin());
		do
		{
			fruit_ += (area_->width + 1);
			if (fruit_ >= area_->end()) {
				fruit_ -= (area_->end() - area_->begin());
			}
		} while (fruit_->get_id() != type_id::None);
		
		set_fruit(fruit_, fruit_value::Banana);
		
		move_snake_into_none(field);
	}
	
	
	// Ticks
	
	void tick() {
		switch(state_) {
			case(game_state::Idle) : idle_tick(); break;
			case(game_state::Playing) : playing_tick(); break;
		}
	}
	
	void idle_tick() {
		controller_->update();
		if (controller_->Start) {
			state_ = game_state::Playing;
		}
	}
	
	void playing_tick() {
		controller_->update();
		
		if (controller_->Start) {
			state_ = game_state::Idle;
			return;
		}
		
		if (controller_->Select) {
			reset_game();
			return;
		}
		
		move_snake(controller_->Direction);
		update_screen();
	}
	
	private:
	
	BUFFER* buffer_;
	AREA* area_;
	SnakeController* controller_;
	
	Snake snake_;
	Field* fruit_;
	game_state state_;
	uint8_t score_ = 0;
};



#endif /* GAME_H_ */