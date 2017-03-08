/*
 * enums.h
 *
 * Created: 3/8/2017 7:36:20 PM
 *  Author: live
 */ 

#ifndef NES_ENUMS_H_
#define NES_ENUMS_H_

namespace NES {
	enum ButtonOrder : uint8_t
	{
		A		= 7,
		B		= 6,
		Select	= 5,
		Start	= 4,
		Up		= 3,
		Down	= 2,
		Left	= 1,
		Right	= 0
	};
}

#endif /* NES_ENUMS_H_ */