/*
 * Enums.h
 *
 * Created: 3/12/2017 10:58:15 PM
 *  Author: live
 */ 


#ifndef SPI_ENUMS_H_
#define SPI_ENUMS_H_

namespace SPI {
	enum Order : unsigned char
	{
		MSB_FIRST = 0,
		LSB_FIRST = 1
	};

	enum Prescale : unsigned char
	{
		SCK_FREQ_PRESCALE_4 = 0
	};
	
	template<typename T>
	struct Mode {
		static uint8_t const value = (T::cpol * 2) + T::cpha;
	};
	
	struct SampleRisingSetupFalling : Mode<SampleRisingSetupFalling> {
		static uint8_t const cpol = 0;
		static uint8_t const cpha = 0;
	};
	
	struct SetupRisingSampleFalling : Mode<SetupRisingSampleFalling> {
		static uint8_t const cpol = 0;
		static uint8_t const cpha = 1;
	};
	
	struct SampleFallingSetupRising : Mode<SampleFallingSetupRising> {
		static uint8_t const cpol = 1;
		static uint8_t const cpha = 0;
	};
	
	struct SetupFallingSampleRising : Mode<SetupFallingSampleRising> {
		static uint8_t const cpol = 1;
		static uint8_t const cpha = 1;
	};
}



#endif /* SPI_ENUMS_H_ */