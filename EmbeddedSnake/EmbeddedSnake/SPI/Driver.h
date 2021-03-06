/*
* SPIDriver.h
*
* Created: 16/02/2017 14:55:55
* Author: KasperSK
*/


#ifndef __SPIDRIVER_H__
#define __SPIDRIVER_H__

#include <avr/io.h>
#include "Enums.h"

namespace SPI {

	template <Order ORDER, typename MODE, Prescale PRESCALE>
	class Driver
	{
	public:
		
		static inline void Init();

		static inline void Write(unsigned char bits);
		
		static inline void Enable();
		
		static inline void Disable();
		
		enum class Pins : uint8_t
		{
			Clock  = PB7,
			Miso   = PB6,
			Mosi   = PB5,
			Enable = PB4
			
		};

	private:
		static const unsigned char Order = static_cast<uint8_t>(ORDER);
		static const unsigned char Mode = MODE::value;
		static const unsigned char Prescale = static_cast<uint8_t>(PRESCALE);
	};
	
	template <Order ORDER, typename MODE, Prescale PRESCALE>
	void Driver<ORDER, MODE, PRESCALE>::Init() {
		// Setup SPI Pins communication
		DDRB |= (1 << Pins::Clock)|(1 << Pins::Mosi)|(1 << Pins::Enable);
		DDRB &= ~(1 << Pins::Miso);

		// Set SCE high, since it is active low
		//PORTB |= (1 << PB4);
		
		// Register setup
		SPCR |= ((1 << SPE)|(1 << MSTR)|(Order << DORD)|(Mode << CPHA)|(((Prescale << 5) >> 5) << SPR0));
		SPSR |= ((Prescale >> 2) << SPI2X);
	}

	template <Order ORDER, typename MODE, Prescale PRESCALE>
	void Driver<ORDER, MODE, PRESCALE>::Write(unsigned char bits) {
		// Set SCE low
		//PORTB &= ~(1 << PB4);
	
		// Start transmission and wait
		SPDR = bits;
		while(!(SPSR & (1 << SPIF)));
	
		// Set SCE high
		//PORTB |= (1 << PB4);
	}

	template <Order ORDER, typename MODE, Prescale PRESCALE>
	void Driver<ORDER, MODE, PRESCALE>::Enable() {
		PORTB &= ~(1 << Pins::Enable);
	}
	
	template <Order ORDER, typename MODE, Prescale PRESCALE>
	void Driver<ORDER, MODE, PRESCALE>::Disable() {
		PORTB |= (1 << Pins::Enable);
	}

	template<typename U>
	int operator << (const int& ch, const U& pin)
	{
		return ch << static_cast<uint8_t>(pin);
	}

}
#endif //__SPIDRIVER_H__