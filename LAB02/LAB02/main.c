/*
 * LAB02.c
 *
 * Created: 26/01/2017 09:40:52
 * Author : KasperSK
 */ 

#include <avr/io.h>
#define F_CPU 3686400
#include <avr/delay.h>

int main()
{
	unsigned char i = 0;
	
	DDRA = 0;    //PORTA pins are inputs (SWITCHES)
	DDRB = 0xFF; //PORTB pins are outputs (LEDs)
	while (1)
	{
		PORTB = ~i; //Display "i" at the LEDs
		i++;
		_delay_ms(500);
		if ((PINA & 0b10000000)==0)
			i = 0;
	}
	return 0;
}
