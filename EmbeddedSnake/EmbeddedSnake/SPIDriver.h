/* 
* SPIDriver.h
*
* Created: 16/02/2017 14:55:55
* Author: KasperSK
*/


#ifndef __SPIDRIVER_H__
#define __SPIDRIVER_H__

#include <avr/io.h>


enum SPIDataOrder : unsigned char
{
	MSB_FIRST = 0,
	LSB_FIRST = 1
};

template<SPIDataOrder> struct Order {};

template<> struct Order<SPIDataOrder::MSB_FIRST>
{
	static const unsigned char value = SPIDataOrder::MSB_FIRST;
};

template<> struct Order<SPIDataOrder::LSB_FIRST>
{
	static const unsigned char value = SPIDataOrder::LSB_FIRST;
};

enum SPIMode : unsigned char
{
	SAMPLE_RISING_SETUP_FALLING = 0,
	SETUP_RISING_SAMPLE_FALLING = 1,
	SAMPLE_FALLING_SETUP_RISING = 2,
	SETUP_FALLING_SAMPLE_RISING = 3
};

template<SPIMode> struct Mode {};

template<> struct Mode<SAMPLE_RISING_SETUP_FALLING>
{
	static const unsigned char value = SPIMode::SAMPLE_RISING_SETUP_FALLING;
};

template<> struct Mode<SETUP_RISING_SAMPLE_FALLING>
{
	static const unsigned char value = SPIMode::SETUP_RISING_SAMPLE_FALLING;
};

template<> struct Mode<SAMPLE_FALLING_SETUP_RISING>
{
	static const unsigned char value = SPIMode::SAMPLE_FALLING_SETUP_RISING;
};

template<> struct Mode<SETUP_FALLING_SAMPLE_RISING>
{
	static const unsigned char value = SPIMode::SETUP_FALLING_SAMPLE_RISING;
};

enum SPIPrescale : unsigned char
{
	SCK_FREQ_PRESCALE_4 = 0
};

template<SPIPrescale> struct Prescale {};

template<> struct Prescale<SPIPrescale::SCK_FREQ_PRESCALE_4>
{
	static const unsigned value = SPIPrescale::SCK_FREQ_PRESCALE_4;
};

template <SPIDataOrder ORDER, SPIMode MODE, SPIPrescale PRESCALE>
class SPIDriver
{
public:
	SPIDriver()
	{
		// Setup ports for SPI communication
		// PB7: SCLK
		// PB5: MOSI
		// PB4: SCE
		DDRB |= (1 << PB7)|(1 << PB5)|(1 << PB4);

		// Set SCE high, since it is active low
		//PORTB |= (1 << PB4);
		
		// Register setup
		SPCR |= ((1 << SPE)|(1 << MSTR)|(Order << DORD)|(Mode << CPHA)|(((Prescale << 5) >> 5) << SPR0));
		SPSR |= ((Prescale >> 2) << SPI2X);
	}

	void Write(unsigned char bits)
	{
		// Set SCE low
		//PORTB &= ~(1 << PB4);
		
		// Start transmission and wait
		SPDR = bits;
		while(!(SPSR & (1 << SPIF)));
		
		// Set SCE high
		//PORTB |= (1 << PB4);
	}

private:
	static const unsigned char Order = Order<ORDER>::value;
	static const unsigned char Mode = Mode<MODE>::value;
	static const unsigned char Prescale = Prescale<PRESCALE>::value;
};

#endif //__SPIDRIVER_H__