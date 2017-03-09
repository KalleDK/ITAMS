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
		
		using size_type = typename area_type::size_type;
		
		Game(screen_type_ptr screen, area_type_ptr area, controller_type_ptr controller) : screen_(screen), area_(area), controller_(controller)
		{
		}
		
		void init() {
			screen_->init();
			goto_reset();
		}
		
		void refresh_screen() {
			screen_->update();
		}
		
		void show_playing_area() {
			for (field_type_ptr itr = area_->begin(); itr != area_->end(); ++itr) {
				auto id = itr->get_id();
				auto point = area_->get_point(itr);
				switch(id){
					case(type_id::Fruit)  : screen_->draw_fruit(point);
										    break;
					case(type_id::Snake)  : screen_->draw_snake(point, itr->get_snake());
										    break;
					case(type_id::None)   : screen_->draw_none(point);
											break;
					case(type_id::Border) : screen_->draw_border(point, itr->get_border());
											break;
				}
			}
		}
		
		void show_win_menu() {
			screen_->draw_win_menu(score_);
		}
		
		void show_game_over_menu() {
			screen_->draw_game_over_menu(score_);
		}
		
		void show_idle_menu() {
			screen_->draw_idle_menu();
		}
		
		// Setting and updating fields -> these should call their own drawing functions if needed
		
		void set_none(field_type_ptr field) {
			
			field->set_none();
			
			screen_->draw_none(area_->get_point(field));
		}
		
		void set_border(field_type_ptr field, border_value direction) {
			
			field->set_border(direction);
			
			screen_->draw_border(area_->get_point(field), direction);
		}
		
		void set_snake(field_type_ptr field, Direction direction) {
			
			field->set_snake(direction);
			
			screen_->draw_snake(area_->get_point(field), direction);
		}
		
		void set_fruit(field_type_ptr field, fruit_value value) {
			
			field->set_fruit(value);
			
			screen_->draw_fruit(area_->get_point(field));
		}
		
		
		
		// Adding items to the game or removing
		
		void add_area() {
			
			for (field_type_ptr itr = area_->begin(); itr != area_->end(); ++itr) {
				itr->set_none();
			}
			
			screen_->clear();
			
		}
		
		void add_border() {
			
			for (uint8_t x = 1; x < area_->width - 1; ++x) {
				set_border(area_->get_field(x, 0), border_value::North);
				set_border(area_->get_field(x, area_->height - 1), border_value::South);
			}
			
			for (uint8_t y = 1; y < area_->height - 1; ++y) {
				set_border(area_->get_field(0, y), border_value::West);
				set_border(area_->get_field(area_->width - 1, y), border_value::East);
			}
			
			set_border(area_->get_field(0                , 0                 ), border_value::NorthWest);
			set_border(area_->get_field(area_->width - 1 , 0                 ), border_value::NorthEast);
			set_border(area_->get_field(0                , area_->height - 1 ), border_value::SouthWest);
			set_border(area_->get_field(area_->width - 1 , area_->height - 1 ), border_value::SouthEast);

		}
		
		void add_fruit(uint8_t x, uint8_t y, fruit_value value) {
			
			fruit_ = fruit_type_ptr(area_->get_field(x,y));
			
			set_fruit(fruit_, value);
		}
		
		void add_snake(uint8_t x, uint8_t y, Direction direction, size_type size) {
			
			snake_ = snake_type(area_->get_field(x,y), direction, size);
			
			set_snake(snake_.head, Direction::None);
		}
		

		// Snake functions

		void kill_snake() {
			snake_.is_alive = false;
			player_ = player_state::Lost;
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
			set_snake(snake_.head, snake_.direction);
			
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
			
			tick_ = 0;
			free_spaces = ((area_->width - 2) * (area_->height - 2)) - 1;
			state_ = game_state::Playing;
			player_ = player_state::Playing;
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
				if (free_spaces == 0) {
					player_ = player_state::Won;
				}
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
			show_win_menu();
			refresh_screen();
		}
		
		void goto_game_over() {
			state_ = game_state::GameOver;
			show_game_over_menu();
			refresh_screen();
		}
		
		void goto_reset() {
			reset_game();
			goto_playing();
		}
		
		void goto_playing() {
			state_ = game_state::Playing;
			show_playing_area();
			refresh_screen();
		}
		
		void goto_idle() {
			state_ = game_state::Idle;
			show_idle_menu();
			refresh_screen();
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
			} else {
				tick_ = 0;	
			}

			
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
			
			screen_->update();
			
			switch(player_) {
				case(player_state::Won)  : goto_win(); return;
				case(player_state::Lost) : goto_game_over(); return;
				default: break;
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
		player_state player_;
		uint8_t tick_;
		size_type score_;
		size_type free_spaces;
	};

}

#endif /* GAME_H_ */