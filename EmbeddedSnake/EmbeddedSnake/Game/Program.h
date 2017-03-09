/*
* Program.h
*
* Created: 3/9/2017 3:51:17 PM
*  Author: live
*/


#ifndef GAME_PROGRAM_H_
#define GAME_PROGRAM_H_

namespace Game {
	

	template<typename GAME, typename CONTROLLER, typename SCREEN>
	class Program {
	
	public:
		using game_type     = GAME;
		using game_type_ptr = game_type*;

		using screen_type     = SCREEN;
		using screen_type_ptr = screen_type*;
		
		using controller_type     = CONTROLLER;
		using controller_type_ptr = controller_type*;
		
	public:
		template<typename SCREENBUFFER>
		Program(controller_type_ptr controller, SCREENBUFFER screen_buffer) : screen(screen_buffer), game(&screen), controller(controller) {};
		
		void init() {
			game.init();
			goto_reset();
		}
		
		void tick() {
			switch(state) {
				case(program_state::Idle) : idle_tick(); break;
				case(program_state::Playing) : playing_tick(); break;
				case(program_state::Win) : win_tick(); break;
				case(program_state::GameOver) : game_over_tick(); break;
				default: break;
			}
		}
		
	private:
	
		// Transitions
	
		void goto_win() {
			state = program_state::Win;
			game.show_win_menu();
		}
		
		void goto_game_over() {
			state = program_state::GameOver;
			game.show_game_over_menu();
		}
		
		void goto_reset() {
			game.reset();
			goto_playing();
		}
		
		void goto_playing() {
			state = program_state::Playing;
			game.show_playing_area();
		}
		
		void goto_idle() {
			state = program_state::Idle;
			game.show_idle_menu();
		}
		
		// State Ticks
		
		void idle_tick() {
			controller->update();
			if (controller->a) {
				goto_playing();
				return;
			}
			if (controller->select) {
				goto_reset();
				return;
			}
		}
		
		void playing_tick() {
			
			switch(game.get_player_state()) {
				case(player_state::Won)  : goto_win(); return;
				case(player_state::Lost) : goto_game_over(); return;
				default: break;
			}
			
			controller->update();
			
			if (controller->start) {
				goto_idle();
				return;
			}
			
			if (controller->select) {
				goto_reset();
				return;
			}
			
			if (controller->up) {
				game.pushed_up();
				return;
			}

			if (controller->down) {
				game.pushed_down();
				return;
			}
			
			if (controller->left) {
				game.pushed_left();
				return;
			}
			
			if (controller->right) {
				game.pushed_right();
				return;
			}
			
			if (controller->a) {
				game.pushed_a();
				return;
			}
			
			if (controller->b) {
				game.pushed_b();
				return;
			}
			
			game.pushed_none();
			return;
			
			
		}
		
		void win_tick() {
			controller->update();
			if (controller->a) {
				goto_reset();
				return;
			}
		}
		
		void game_over_tick() {
			controller->update();
			if (controller->a) {
				goto_reset();
				return;
			}
		}
		
	private:
		screen_type screen;
		game_type game;
		controller_type_ptr controller;
		program_state state;
	};


}
#endif /* GAME_PROGRAM_H_ */