#ifndef GAME_H_
#define GAME_H_



#include "Enums.h"
#include "Area.h"
#include "Snake.h"

namespace Game {

	template<typename SCREEN, typename AREA, typename CONTROLLER, uint8_t TICK_DIVIDER>
	class Game
	{
		public:

		using screen_type     = SCREEN;
		using screen_type_ptr = screen_type*;
		
		using area_type     = AREA;
		using area_type_ptr = area_type*;
		
		using controller_type     = CONTROLLER;
		using controller_type_ptr = controller_type*;
		
		using field_type     = typename area_type::value_type;
		using field_type_ptr = typename area_type::value_type_ptr;
		
		using fruit_type     = typename area_type::value_type;
		using fruit_type_ptr = typename area_type::value_type_ptr;
		
		using snake_type = Snake<typename area_type::value_type, Direction>;
		using screen_point = typename screen_type::point;
		
		using size_type = typename area_type::size_type;
		
		Game(screen_type_ptr screen, area_type_ptr area, controller_type_ptr controller) : screen_(screen), area_(area), controller_(controller)
		{
			reset_game();
		}
		
		// Drawing and screen functions
		
		void clear_area() {
			screen_->clear();
		}
		
		void draw_idle_menu() {
			screen_->draw_square_with_border(screen_point{4, 6}, 8, 10, 1);
			
			screen_->set_data(9, 1, 0b00011110);
			screen_->set_data(8, 1, 0b00101000);
			screen_->set_data(7, 1, 0b00101000);
			screen_->set_data(6, 1, 0b00011110);
		}
		
		void draw_win_menu(size_type score) {
			screen_->draw_square_with_border(screen_point{4, 6}, 8, 10, 1);
			
			screen_->set_data(9, 1, 0b00011110);
			screen_->set_data(8, 1, 0b00101000);
			screen_->set_data(7, 1, 0b00101000);
			screen_->set_data(6, 1, 0b00011110);
		}
		
		void draw_game_over_menu(size_type score) {
			screen_->draw_square_with_border(screen_point{4, 6}, 8, 10, 1);
			
			screen_->set_data(9, 1, 0b00011110);
			screen_->set_data(8, 1, 0b00101000);
			screen_->set_data(7, 1, 0b00101000);
			screen_->set_data(6, 1, 0b00011110);
		}
		
		void draw_playing_area() {
			for (field_type_ptr itr = area_->begin(); itr != area_->end(); ++itr) {
				switch(itr->get_id()){
					case(type_id::Fruit)  : draw_fruit(itr); break;
					case(type_id::Snake)  : draw_snake(itr); break;
					case(type_id::None)   : draw_none(itr); break;
					case(type_id::Border) : break;
				}
			}
		}
		
		void draw_fruit(field_type_ptr field)
		{
			screen_point p = area_->get_coordinate(field);
			
			screen_->clear_square(p, 3, 3);
			screen_->draw_square(screen_point { p.x + 1  , p.y     }, 1, 1);
			screen_->draw_square(screen_point { p.x      , p.y + 1 }, 1, 1);
			screen_->draw_square(screen_point { p.x + 2  , p.y + 1 }, 1, 1);
			screen_->draw_square(screen_point { p.x + 1  , p.y + 2 }, 1, 1);
		}
		
		void draw_border() {
			//buffer_->draw_border(screen_point{2,2},79,43,1);
			screen_->draw_border(screen_point{0,0},83,47,1);
		}
		
		void draw_snake(field_type_ptr field) {
			screen_point p = area_->get_coordinate(field);
			
			switch(field->get_snake()) {
				case(Direction::Up) : screen_->draw_square(screen_point{p.x, p.y - 1}, 3, 4); break;
				case(Direction::Down) : screen_->draw_square(p, 3, 4); break;
				case(Direction::Left) : screen_->draw_square(screen_point{p.x - 1, p.y}, 4, 3); break;
				case(Direction::Right) : screen_->draw_square(p, 4, 3); break;
				default: screen_->draw_square(p, 3, 3); break;
			}
		}
		
		void draw_none(field_type_ptr field) {
			screen_point p = area_->get_coordinate(field);
			
			screen_->clear_square(screen_point{p.x - 1, p.y - 1}, 5, 5);
		}
		
		void update_screen() {
			screen_->update();
		}
		
		
		
		// Setting and updating fields -> these should call their own drawing functions if needed
		
		void set_fruit(field_type_ptr field, fruit_value value) {
			field->set_fruit(value);
			
			draw_fruit(field);
		}
		
		void set_none(field_type_ptr field) {
			field->set_none();
			
			draw_none(field);
		}
		
		void set_border(field_type_ptr field) {
			field->set_border();
		}
		
		void set_snake(field_type_ptr field, Direction direction) {
			field->set_snake(direction);
			
			draw_snake(field);
		}
		
		void update_snake(field_type_ptr field, Direction direction) {
			field->set_snake(direction);
			draw_snake(field);
		}
		
		
		
		// Adding items to the game or removing
		
		void add_area() {
			
			for (field_type_ptr itr = area_->begin(); itr != area_->end(); ++itr) {
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
		
		void add_snake(uint8_t x, uint8_t y, Direction direction, size_type size) {
			snake_ = snake_type(area_->get_field(x,y), direction, size);
			
			set_snake(snake_.head, Direction::None);
		}
		

		// Snake functions

		void kill_snake() {
			snake_.is_alive = false;
		};

		void move_snake_tail() {
			// Move tail
			field_type_ptr old_tail = snake_.tail;
			
			Direction tail_direction = snake_.tail->get_snake();
			snake_.tail = area_->get_neighbour(snake_.tail, tail_direction);
			
			set_none(old_tail);
			
		}

		void move_snake_head(field_type_ptr field) {
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
			add_snake(9, 5, Direction::Right, 3);
			
			update_screen();
			
			tick_ = 0;
			free_spaces = ((area_->width - 2) * (area_->height - 2)) - 1;
			state_ = game_state::Playing;
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
			
			field_type_ptr field = area_->get_neighbour(snake_.head, snake_.direction);
			
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
			if ((field == snake_.tail) && (snake_.grow == 0) ) {
				move_snake_into_none(field);
				} else {
				kill_snake();
			}
		}
		
		void move_snake_into_none(field_type_ptr field) {
			
			if (snake_.grow == 0) {
				move_snake_tail();
				} else {
				--snake_.grow;
				--free_spaces;
			}
			
			move_snake_head(field);
			
		}
		
		void move_snake_into_fruit(field_type_ptr field) {
			
			++snake_.grow;
			++score_;
			
			move_snake_into_none(field);
			
			if (free_spaces > 0) {
				fruit_ = snake_.tail + (snake_.head-area_->begin());
				do
				{
					fruit_ += (area_->width + 1);
					if (fruit_ >= area_->end()) {
						fruit_ -= (area_->end() - area_->begin());
					}
				} while (fruit_->get_id() != type_id::None);
				
				set_fruit(fruit_, fruit_value::Banana);
			}
			
		}
		
		
		// Ticks
		
		
		
		void goto_win() {
			state_ = game_state::Win;
			draw_win_menu(score_);
			update_screen();
		}
		
		void goto_game_over() {
			state_ = game_state::GameOver;
			draw_game_over_menu(score_);
			update_screen();
		}
		
		void goto_reset() {
			reset_game();
			goto_playing();
		}
		
		void goto_playing() {
			state_ = game_state::Playing;
			draw_playing_area();
			update_screen();
		}
		
		void goto_idle() {
			state_ = game_state::Idle;
			draw_idle_menu();
			update_screen();
		}
		
		
		void tick() {
			switch(state_) {
				case(game_state::Idle) : idle_tick(); break;
				case(game_state::Playing) : playing_tick(); break;
				case(game_state::Win) : win_tick(); break;
				case(game_state::GameOver) : game_over_tick(); break;
				default: break;
			}
		}
		
		void idle_tick() {
			controller_->update();
			if (controller_->a) {
				goto_playing();
				return;
			}
			if (controller_->select) {
				goto_reset();
				return;
			}
		}
		
		void playing_tick() {
			
			controller_->update();
			
			if (controller_->start) {
				goto_idle();
				return;
			}
			
			if (controller_->select) {
				goto_reset();
				return;
			}
			
			if (tick_ < TICK_DIVIDER) {
				++tick_;
				return;
			}
			
			
			
			tick_ = 0;
			
			if (controller_->up) {
				move_snake(Direction::Up);
				} else if (controller_->down) {
				move_snake(Direction::Down);
				} else if (controller_->left) {
				move_snake(Direction::Left);
				} else if (controller_->right) {
				move_snake(Direction::Right);
				} else {
				move_snake(Direction::None);
			}
			
			update_screen();
			
			if (!snake_.is_alive) {
				goto_game_over();
				return;
			}
			
			if (free_spaces == 0) {
				goto_win();
				return;
			}
		}
		
		void win_tick() {
			controller_->update();
			if (controller_->a) {
				goto_reset();
				return;
			}
		}
		
		void game_over_tick() {
			controller_->update();
			if (controller_->a) {
				goto_reset();
				return;
			}
		}
		
		
		
		private:
		
		
		
		screen_type_ptr screen_;
		area_type_ptr area_;
		controller_type_ptr controller_;
		snake_type snake_;
		
		fruit_type_ptr fruit_;
		
		game_state state_;
		uint8_t tick_;
		size_type score_;
		size_type free_spaces;
	};

}

#endif /* GAME_H_ */