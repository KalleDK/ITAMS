/*
 * Blinky.c
 *
 * Created: 06/02/2017 12:39:52
 * Author : KasperSK
 */ 

#define F_CPU 3686400UL
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "switch.h"

int main(void)
{
	initLEDport();
	initSwitchPort();
	
    /* Replace with your application code */
    while (1) 
    {
		writeAllLEDs(switchStatus());		
		_delay_ms(200);
    }
}

