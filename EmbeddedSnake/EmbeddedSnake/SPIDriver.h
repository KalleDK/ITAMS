/* 
* SPIDriver.h
*
* Created: 16/02/2017 14:55:55
* Author: KasperSK
*/


#ifndef __SPIDRIVER_H__
#define __SPIDRIVER_H__

#include <avr/io.h>


template <unsigned char ORDER, unsigned char MODE, unsigned char DIVIDER> 
class SPIDriver
{
////variables
//public:
//enum DataOrder : unsigned char
//{
	//MSB = 0,
	//LSB = 1
//};
//
//enum SPIMode : unsigned char
//{
	//Zero = 0,
	//One = 1,
	//Two = 2,
	//Three = 3
//};
//
//enum Divider : unsigned char
//{
	//Four = 0,
	//Sixteen = 1,
	//SixtyFour = 2,
	//HunderedAndTwentyEight = 3,
	//TwoSad = 4,
	//Eight = 5,
	//ThirtyTwo = 6,
	//SixtyFourAgain = 7
//};
//protected:
//private:

//functions
public:
	SPIDriver();
	~SPIDriver();
	
	unsigned char Write(unsigned char);
	void SetDataOrder(SPIDriver::DataOrder order);
	void SetSPIMode(SPIDriver::SPIMode mode);
	void SetFrequencyDivder(SPIDriver::Divider clockDivider);
protected:
private:
	SPIDriver( const SPIDriver &c );
	SPIDriver& operator=( const SPIDriver &c );

}; //SPIDriver

#endif //__SPIDRIVER_H__
