/*************************************************
* "LED.C":                                       *
* Implementation file for the STK500 LED driver. *
* The LEDs are connected to PC pins.             *
* Henning Hargaard, 26/3 2012                    *
**************************************************/
#include <avr/io.h>

#define MAX_LED_NR 7

void initLEDport()
{
	PORTB = 0xFF;
	DDRB = 0xFF;
}

void writeAllLEDs(unsigned char pattern)
{
  // Hent parameteren, vend alle bit, og skriv til lysdioderne
  // Bittene skal vendes, da HW er indrettet, 
  // så et 0 vil tænde en lysdiode
  PORTB = ~pattern;   
}

void turnOnLED(unsigned char led_nr)
{
// Lokal variabel
unsigned char mask;
  // Vi skal kun lave noget, hvis led_nr < 8
  if (led_nr <= MAX_LED_NR)
  {
    // Dan maske på basis af parameteren (led_nr)
    mask = ~(0b00000001 << led_nr);
    // Tænd den aktuelle lysdiode (de andre ændres ikke)
    PORTB = PINB & mask;
  }   
}

void turnOffLED(unsigned char led_nr)
{
	unsigned char mask;
	if(led_nr <= MAX_LED_NR)
	{
		mask = (0b00000001 << led_nr);
		PORTB = PINB | mask; 
	}
}

void toggleLED(unsigned char led_nr)
{
	unsigned char mask;
	if(led_nr <= MAX_LED_NR)
	{
		mask = (0b00000001 << led_nr);
		PORTB = PINB ^ mask;
	}
}
