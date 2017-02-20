#include <avr/io.h>
#define F_CPU 3686400
#include <util/delay.h>
#include "SPIDriver.h"

int main()
{
	SPIDriver<SPIDataOrder::LSB_FIRST, SPIMode::SETUP_FALLING_SAMPLE_RISING, SPIPrescale::SCK_FREQ_PRESCALE_4> spi;

	while (1) 
	{
		_delay_ms(500);
		spi.Write(0b10000001);
	}

	return 0;
}

