/*
* Field.h
*
* Created: 3/8/2017 8:19:57 PM
*  Author: live
*/


#ifndef GAME_FIELD_H_
#define GAME_FIELD_H_

#include "Enums.h"

namespace Game {
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

}
#endif /* GAME_FIELD_H_ */