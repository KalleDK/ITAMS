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
		
		Snake(FIELD* field, DIRECTION direction, uint16_t grow) : head(field), tail(field), grow(grow), is_alive(true), direction(direction) {};

		FIELD* head;
		FIELD* tail;
		
		uint16_t grow;
		
		bool is_alive;
		
		DIRECTION direction;
		
	};
}



#endif /* GAME_SNAKE_H_ */