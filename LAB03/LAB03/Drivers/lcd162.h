/*
 * lcd162.h
 *
 * Driver for the PowerTip PC1602-F alphanumeric display.
 * Display controller = HD44780U (LCD-II).
 *
 * Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)
 *
 * Connection : PORTx (4 bit mode) :
 * [LCD]	            [Portx]
 * RS (pin4)  ------  bit 0
 * RW (pin 5) ------  bit 1
 * E  (pin 6) ------  bit 2
 * DB4 (pin 11) ---   bit 4
 * DB5 (pin 12) ---   bit 5
 * DB6 (pin 13) ---   bit 6
 * DB7 (pin 14) ---   bit 7
 *
 * Created: 30/01/2017 08:33:49
 *  Author: KasperSK
 */ 


#ifndef LCD162_H_
#define LCD162_H_

// (here PORTC is used) :
#define DDR_lcd	 DDRC
#define PIN_lcd	 PINC
#define PORT_lcd PORTC

//  Public:
void LCDInit();
void LCDClear();
void LCDGotoXY(unsigned char x, unsigned char y);
void LCDDispChar(char ch);
void LCDDispString(char *str);
void LCDDispInteger(int i);
void LCDLoadUDC(unsigned char UDCNo, const unsigned char *UDCTab);
void LCDOnOffControl(unsigned char cursor, unsigned char blink);
void LCDCursorLeft();
void LCDCursorRight();
void LCDShiftLeft();
void LCDShiftRight();




#endif /* LCD162_H_ */