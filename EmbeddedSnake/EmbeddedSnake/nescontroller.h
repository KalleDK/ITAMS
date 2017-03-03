/*
 * nescontroller.h
 *
 * Created: 3/3/2017 2:35:11 PM
 *  Author: live
 */ 


#ifndef NESCONTROLLER_H_
#define NESCONTROLLER_H_

#include "TC4021.h"

enum NESDirection : uint8_t
{
	None = 0,
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4
};

struct NESButtons {
	bool A;
	bool B;
	bool Start;
	bool Select;
	NESDirection Direction;
	
	NESButtons() : NESButtons(0x00) {};
	
	NESButtons(const uint8_t& data) {
		A = !!(data & (1 << 7));
		B = !!(data & (1 << 6));
		Select = !!(data & (1 << 5));
		Start = !!(data & (1 << 4));
		switch (data & 0b00001111) {
			case 0b0001: Direction = Right;
					 break;
			case 0b0010: Direction = Left;
					 break;
			case 0b0100: Direction = Down;
					 break;
			case 0b1000: Direction = Up;
					 break;
			default: Direction = None;
					 break;
		}
	}
};

template<typename DATAPIN, typename LATCH, typename CLOCK>
struct NESController : TC4021<uint8_t, 8, DATAPIN, LATCH, CLOCK> {
	
	using base = TC4021<uint8_t, 8, DATAPIN, LATCH, CLOCK>;
	
	bool A;
	bool B;
	bool Start;
	bool Select;
	NESDirection Direction;
	
	void update() {
		uint8_t data = base::read();
		A = !!(data & (1 << 7));
		B = !!(data & (1 << 6));
		Select = !!(data & (1 << 5));
		Start = !!(data & (1 << 4));
		switch (data & 0b00001111) {
			case 0b0001: Direction = Right;
							 break;
			case 0b0010: Direction = Left;
							break;
			case 0b0100: Direction = Down;
							break;
			case 0b1000: Direction = Up;
							break;
			default: Direction = None;
							break;
		}
	}
};

#endif /* NESCONTROLLER_H_ */