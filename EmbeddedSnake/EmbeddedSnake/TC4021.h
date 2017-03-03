/*
 * TC4201.c
 *
 * Created: 3/3/2017 10:12:23 AM
 *  Author: live
 */ 

#ifndef __TC4021_H__
#define __TC4021_H__

#include "timing.h"

//
// A CLOCK PULSE is HIGH to LOW
//
//   --------
//          |
//          |_______
//
// As the clock is HIGH as we enter we don't need to set it
// T_H is how long from we go to HIGH until the new value is
// on the DATA pin. T_SU is how long we have to stay in LOW
// for the IC to setup for the next clock.
//
// The first bit can be read without the clock, therefore
// we only need 7 clock's
//
// The safest place to read is right after we go low,
// as we are sure the data is correct there.
//


template <typename T, uint8_t REGISTER_SIZE, typename DATA, typename LATCH, typename CLOCK>
struct TC4021 {

public:

	static const uint8_t T_rem = 45;
	static const uint8_t T_H = 35;
	static const uint8_t T_SU = 25;
	
	TC4021() {
		LATCH::set_output();
		LATCH::set();
		
		CLOCK::set_output();
		CLOCK::clear();
		
		DATA::set_input();
	}
	
	T read() {
		T buffer;
		
		// Start Transmission:
		LATCH::clear();
		
		_delay_ns(T_rem);
		
		// Read the first bit
		buffer = DATA::read();
		for (auto i = 0; i < REGISTER_SIZE-1; ++i)
		{
			CLOCK::set();
			_delay_ns(T_H);
			CLOCK::clear();
			// Read the rest of the bits one by one
			buffer = buffer << 1 | DATA::read();
			_delay_ns(T_SU);
		}
		
		// End Transmission
		LATCH::set();
		return buffer;
	}
	
};


#endif //__TC4021_H__