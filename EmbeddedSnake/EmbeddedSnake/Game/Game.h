#ifndef GAME_H_
#define GAME_H_



#include "Enums.h"
#include "Area.h"
#include "Snake.h"

namespace Game {

	template<typename SCREEN, typename AREA, uint8_t TICK_DIVIDER>
	class Game
	{
		public:

		using screen_type     = SCREEN;
		using screen_type_ptr = screen_type*;
		
		using area_type     = AREA;
		using area_type_ptr = area_type*;
		
		using field_type     = typename area_type::value_type;
		using field_type_ptr = typename area_type::value_type_ptr;
		
		using fruit_type     = typename area_type::value_type;
		using fruit_type_ptr = typename area_type::value_type_ptr;
		
		using snake_type = Snake<typename area_type::value_type, Direction>;
		
		using size_type = typename area_type::size_type;
		
		area_type area_;
		
		Game(screen_type_ptr screen) : screen(screen), area(&area_) 
		{
		}
		
		
		void init() {
			screen->init();
		}
		
		void reset() {
			
			add_area();
			add_border();
			add_fruit(5, 4, fruit_value::Apple);
			add_snake(9, 5, Direction::Right, 3);
			
			tick = 0;
			free_spaces = ((area->width - 2) * (area->height - 2)) - 1;
			player = player_state::Playing;
		}
		
		player_state get_player_state() {
			return player;
		}
		
		uint8_t get_player_score() {
			return score;
		}
		
		void show_playing_area() {
			for (field_type_ptr itr = area->begin(); itr != area->end(); ++itr) {
				auto id = itr->get_id();
				auto point = area->get_point(itr);
				switch(id){
					case(type_id::Fruit)  : screen->draw_fruit(point);
										    break;
					case(type_id::Snake)  : screen->draw_snake(point, itr->get_snake());
										    break;
					case(type_id::None)   : screen->draw_none(point);
											break;
					case(type_id::Border) : screen->draw_border(point, itr->get_border());
											break;
				}
			}
			refresh_screen();
		}
		
		void show_win_menu() {
			screen->draw_win_menu(score);
			refresh_screen();
		}
		
		void show_game_over_menu() {
			screen->draw_game_over_menu(score);
			refresh_screen();
		}
		
		void show_idle_menu() {
			screen->draw_idle_menu();
			refresh_screen();
		}
		
		
		
		void pushed_left() {
			if (skip()) {return;}
			move_snake(Direction::Left);
			refresh_screen();
		}
		
		void pushed_right() {
			if (skip()) {return;}
			move_snake(Direction::Right);
			refresh_screen();
		}
		
		void pushed_up() {
			if (skip()) {return;}
			move_snake(Direction::Up);
			refresh_screen();
		}
		
		void pushed_down() {
			if (skip()) {return;}
			move_snake(Direction::Down);
			refresh_screen();
		}
		
		void pushed_a() {
			if (skip()) {return;}
			move_snake(Direction::None);
			refresh_screen();
		}
		
		void pushed_b() {
			if (skip()) {return;}
			move_snake(Direction::None);
			refresh_screen();
		}
		
		void pushed_none() {
			if (skip()) {return;}
			move_snake(Direction::None);
			refresh_screen();
		}
		
		
	private:
		
		bool skip() {
			if (tick < TICK_DIVIDER) {
				++tick;
				return true;
				} else {
				tick = 0;
				return false;
			}
		}
		
		void refresh_screen() {
			screen->update();
		}
		
		
		// Setting and updating fields -> these should call their own drawing functions if needed
		
		void set_none(field_type_ptr field) {
			
			field->set_none();
			
			screen->draw_none(area->get_point(field));
		}
		
		void set_border(field_type_ptr field, border_value direction) {
			
			field->set_border(direction);
			
			screen->draw_border(area->get_point(field), direction);
		}
		
		void set_snake(field_type_ptr field, snake_value direction) {
			
			field->set_snake(direction);
			
			screen->draw_snake(area->get_point(field), direction);
		}
		
		void set_fruit(field_type_ptr field, fruit_value value) {
			
			field->set_fruit(value);
			
			screen->draw_fruit(area->get_point(field));
		}
		
		
		
		// Adding items to the game or removing
		
		void add_area() {
			
			for (field_type_ptr itr = area->begin(); itr != area->end(); ++itr) {
				itr->set_none();
			}
			
			screen->clear();
			
		}
		
		void add_border() {
			
			for (uint8_t x = 1; x < area->width - 1; ++x) {
				set_border(area->get_field(x, 0), border_value::North);
				set_border(area->get_field(x, area->height - 1), border_value::South);
			}
			
			for (uint8_t y = 1; y < area->height - 1; ++y) {
				set_border(area->get_field(0, y), border_value::West);
				set_border(area->get_field(area->width - 1, y), border_value::East);
			}
			
			set_border(area->get_field(0                , 0                 ), border_value::NorthWest);
			set_border(area->get_field(area->width - 1 , 0                 ), border_value::NorthEast);
			set_border(area->get_field(0                , area->height - 1 ), border_value::SouthWest);
			set_border(area->get_field(area->width - 1 , area->height - 1 ), border_value::SouthEast);

		}
		
		void add_fruit(uint8_t x, uint8_t y, fruit_value value) {
			
			fruit = fruit_type_ptr(area->get_field(x,y));
			
			set_fruit(fruit, value);
		}
		
		void add_snake(uint8_t x, uint8_t y, snake_value direction, size_type size) {
			
			snake = snake_type(area->get_field(x,y), direction, size);
			
			set_snake(snake.head, Direction::None);
		}
		

		// Snake functions

		void kill_snake() {
			snake.is_alive = false;
			player = player_state::Lost;
		};

		void move_snake_tail() {
			// Move tail
			field_type_ptr old_tail = snake.tail;
			
			Direction tail_direction = snake.tail->get_snake();
			snake.tail = area->get_neighbour(snake.tail, tail_direction);
			
			set_none(old_tail);
			
		}

		void move_snake_head(field_type_ptr field) {
			// Update old head with direction
			set_snake(snake.head, snake.direction);
			
			// Create new head
			set_snake(field, Direction::None);
			snake.head = field;
		}


		// Movement
		
		void move_snake(Direction direction) {
			// Continue if none is pressed
			direction = (direction != Direction::None ? direction : snake.direction);
			
			// Reversed direction is not allowed
			direction = ((direction == Direction::Right) && (snake.direction == Direction::Left) ? snake.direction : direction);
			direction = ((direction == Direction::Left) && (snake.direction == Direction::Right) ? snake.direction : direction);
			direction = ((direction == Direction::Up) && (snake.direction == Direction::Down) ? snake.direction : direction);
			direction = ((direction == Direction::Down) && (snake.direction == Direction::Up) ? snake.direction : direction);
			
			snake.direction = direction;
			
			field_type_ptr field = area->get_neighbour(snake.head, snake.direction);
			
			switch(field->get_id()) {
				case(type_id::Border) : move_snake_into_border(field); break;
				case(type_id::Snake) : move_snake_into_snake(field); break;
				case(type_id::None) : move_snake_into_none(field); break;
				case(type_id::Fruit) : move_snake_into_fruit(field); break;
			}
			
		}
		
		void move_snake_into_border(field_type_ptr field) {
			kill_snake();
		}
		
		void move_snake_into_snake(field_type_ptr field) {
			if ((field == snake.tail) && (snake.grow == 0) ) {
				move_snake_into_none(field);
				} else {
				kill_snake();
			}
		}
		
		void move_snake_into_none(field_type_ptr field) {
			
			if (snake.grow == 0) {
				move_snake_tail();
				} else {
				--snake.grow;
				--free_spaces;
				if (free_spaces == 0) {
					player = player_state::Won;
				}
			}
			
			move_snake_head(field);
			
		}
		
		void move_snake_into_fruit(field_type_ptr field) {
			
			++snake.grow;
			++score;
			
			move_snake_into_none(field);
			
			if (free_spaces > 0) {
				fruit = snake.tail + (snake.head-area->begin());
				do
				{
					fruit += (area->width + 1);
					if (fruit >= area->end()) {
						fruit -= (area->end() - area->begin());
					}
				} while (fruit->get_id() != type_id::None);
				
				set_fruit(fruit, fruit_value::Banana);
			}
			
		}
		
		
	private:
	
		screen_type_ptr screen;
		area_type_ptr area;
		snake_type snake;
		fruit_type_ptr fruit;
		
		
		player_state player;
			
		uint8_t tick;
		size_type score;
		size_type free_spaces;
	};

}

#endif /* GAME_H_ */