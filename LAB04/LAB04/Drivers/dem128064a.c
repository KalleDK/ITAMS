/*
 * dem128064a.c
 *
 * Created: 30/01/2017 15:45:38
 *  Author: KasperSK
 */ 

#include <avr/io.h>
#include <avr/cpufunc.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "DEM128064A.h"

// Control port pin definitions:
#define CS2  7
#define CS1  6
#define RSTB 5
#define RW   2
#define E    1
#define RS   0

#define LEFT  0
#define RIGHT 1

#define CONTROL 0
#define DATA    1

// LOCAL FUNCTIONS /////////////////////////////////////////////////////////////

// Writes a byte to the display
// "Chip" = LEFT or RIGHT
// "Data" = 8 bit data to be written
// "Type" = CONTROL" or "DATA"
void DisplayWrite(unsigned char Chip, unsigned char Data, unsigned char Type)
{
}

// Reads a byte from the display
// "Chip" = LEFT or RIGHT
// "Type" = CONTROL" or "DATA"
unsigned char DisplayRead(unsigned char Chip, unsigned char Type)
{
}

// Set the display Y address counter (left or right chip)
// "Chip" = LEFT or RIGHT
// "Y" = 0-63
void SetY(unsigned char Chip, unsigned char Y)
{
}

// Set the display page number (left or right chip)
// "Chip" = LEFT or RIGHT
// "Page" = 0-7
void SetPage(unsigned char Chip, unsigned char Page)
{
}

// Sets the display start line (only used for display scroling)
// "Chip" = LEFT or RIGHT
// "StartLinePage = 0-63
void SetStartLine(unsigned char Chip, unsigned char StartLine)
{
}

// Reads and returns the display status byte (left or right chip)
// "Chip" = LEFT or RIGHT
unsigned char Status(unsigned char Chip)
{
}


// Clears all pixels at one of the screens halfes (left or right)
// "Chip" = LEFT or RIGHT
void ClearHalfScreen(unsigned char Chip)
{
}

// PUBLIC FUNCTIONS ////////////////////////////////////////////////////////////

// Initializes (resets) the display
void DisplayInit()
{
}

// Turns the display (both left and right side) ON
void DisplayOn()
{
}

// Turns the display (both left and right side) OFF
void DisplayOff()
{
}

// Clears all pixels at the whole screen (left and right)
void ClearScreen()
{
}

// Displays a graphical image (whole screen)
// The parameter is a pointer to the bit array defining the image
void DisplayPic(const char *picArray)
{
}

// Sets one pixel at x,y
// Notice: x = Horizontal (0-127), y = Vertical (0-63)
// This correspons to the "logical" x and y terms
// in contrast to the display internal definitions
void SetPixel(unsigned char x, unsigned char y)
{
}

// Draws one horizontal line
// "StartX, StartY" is the (logical) start position of the line
// "Length" is the line length in pixels
void Draw_Horizontal_Line(unsigned char StartX, unsigned char StartY, unsigned char Length)
{
}