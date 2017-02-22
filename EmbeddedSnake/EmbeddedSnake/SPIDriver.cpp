/* 
* SPIDriver.cpp
*
* Created: 16/02/2017 14:55:54
* Author: KasperSK
*/


#include "SPIDriver.h"

// default constructor
SPIDriver::SPIDriver()
{
	SPCR |= (1<<SPIE) | (1<<MSTR); // 0b Interupt:0 SPIEN:1 0 1 POL/PHA:11 CLOCK: xx could maybe work
	SPSR = 0;
} //SPIDriver

// default destructor
SPIDriver::~SPIDriver()
{
} //~SPIDriver

unsigned char SPIDriver::Write(unsigned char data){
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}