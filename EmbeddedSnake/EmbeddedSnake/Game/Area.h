/*
 * Area.h
 *
 * Created: 3/8/2017 8:12:38 PM
 *  Author: live
 */ 


#ifndef GAME_AREA_H_
#define GAME_AREA_H_

#include "../Screen/Point.h"

namespace Game {
	
	template<typename FIELD, uint8_t WIDTH, uint8_t HEIGHT>
	class Area {
		
		public:
		
		using size_type = uint16_t;
		
		static const uint8_t height = HEIGHT;
		static const uint8_t width = WIDTH;
		static const size_type size = height * width;
		
		using value_type = FIELD;
		using value_type_ptr = FIELD*;

		value_type screen[size];

		value_type_ptr begin() const {
			return &screen[0];
		}
		
		value_type_ptr end() const {
			return &screen[size];
		}
		
		value_type_ptr end() {
			return &screen[size];
		}
		
		value_type_ptr begin() {
			return &screen[0];
		}
		
		value_type_ptr get_field(uint8_t x, uint8_t y) {
			return begin() + (y * width) + x;
		}
		
		value_type_ptr get_neighbour(value_type_ptr field, Direction direction) {
			switch(direction) {
				case(Direction::Up) : return field - width;
				case(Direction::Down) : return field + width;
				case(Direction::Left) : return field - 1;
				case(Direction::Right) : return field + 1;
				default: return field;
			}
		}
		
		Screen::Point get_coordinate(value_type_ptr field) {
			auto x = ((field - begin()) % width);
			auto y = ((field - begin()) / width);
			return Screen::Point{x * 4 - 2, y * 4 - 2};
		}
		
	};
}



#endif /* GAME_AREA_H_ */