/*
 * LAB01C.c
 *
 * Created: 26/01/2017 09:36:47
 * Author : KasperSK
 */ 

#include <avr/io.h>
#define F_CPU 3686400
#include <avr/delay.h>

int main()
{
	unsigned char i = 0;
	
	DDRB = 0xFF; //PORTB pins are outputs (LEDs)
	while (1)
	{
		PORTB = ~i; //Display "i" at the LEDs
		i++;
		_delay_ms(500);
	}
	return 0;
}

