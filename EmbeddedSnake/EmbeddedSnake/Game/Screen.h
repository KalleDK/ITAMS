/*
 * Screen.h
 *
 * Created: 3/9/2017 1:03:23 PM
 *  Author: live
 */ 


#ifndef SCREEN_H_
#define SCREEN_H_

#include "Point.h"
#include "Enums.h"

namespace Game {
	
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
			buffer_->draw_square_with_border(buffer_point_type{4, 6}, 8, 10, 1);
			
			buffer_->set_data(9, 1, 0b00011110);
			buffer_->set_data(8, 1, 0b00101000);
			buffer_->set_data(7, 1, 0b00101000);
			buffer_->set_data(6, 1, 0b00011110);
		}
		
		template<typename T>
		void draw_win_menu(T score) {
			buffer_->draw_square_with_border(buffer_point_type{4, 6}, 8, 10, 1);
			
			buffer_->set_data(9, 1, 0b00011110);
			buffer_->set_data(8, 1, 0b00101000);
			buffer_->set_data(7, 1, 0b00101000);
			buffer_->set_data(6, 1, 0b00011110);
		}
		
		template<typename T>
		void draw_game_over_menu(T score) {
			buffer_->draw_square_with_border(buffer_point_type{4, 6}, 8, 10, 1);
			
			buffer_->set_data(9, 1, 0b00011110);
			buffer_->set_data(8, 1, 0b00101000);
			buffer_->set_data(7, 1, 0b00101000);
			buffer_->set_data(6, 1, 0b00011110);
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
		
	};

	
	
}




#endif /* SCREEN_H_ */