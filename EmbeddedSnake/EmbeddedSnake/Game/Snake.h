/*
 * Snake.h
 *
 * Created: 3/8/2017 8:21:09 PM
 *  Author: live
 */ 

#ifndef GAME_SNAKE_H_
#define GAME_SNAKE_H_

namespace Game {

	template<typename FIELD, typename DIRECTION>	
	struct Snake {
		
		Snake() = default;
		
		Snake(FIELD* field, DIRECTION direction, uint16_t missing_growth) : head(field), tail(field), direction(direction), missing_growth(missing_growth) {};

		FIELD* head;
		FIELD* tail;
		
		void grow(uint16_t size) {
			missing_growth += size;
		}
		
		uint16_t grew(uint16_t size) {
			missing_growth -= size;
			return size;
		}
		
		uint16_t grew() {
			return grew(1);
		}
		
		bool is_growing() {
			return missing_growth > 0;
		}
		
		DIRECTION direction;
		
		private:
		uint16_t missing_growth;
		
	};
}



#endif /* GAME_SNAKE_H_ */