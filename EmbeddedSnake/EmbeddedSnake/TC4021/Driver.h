/*
* TC4201.c
*
* Created: 3/3/2017 10:12:23 AM
*  Author: live
*/

#ifndef __TC4021_H__
#define __TC4021_H__

#include <util/delay.h>
#include <assert.h>
#include <limits.h>

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

#include "../SPI/DriverSoftware.h"

namespace TC4021 {
	
	template<size_t REGISTER_SIZE>
	using Buffer = SPI::Buffer<REGISTER_SIZE>;
	
	template<typename BUFFER, typename PINS>
	using Driver = SPI::DriverSoftware<BUFFER, PINS, 45, 90, 35, 25>;
	
}




#endif //__TC4021_H__