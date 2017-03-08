/*
 * EmbeddedSnake.cpp
 *
 * Created: 16/02/2017 08:55:11
 * Author : KasperSK
 */ 

#include <avr/io.h>
#include "timing.h"
#include "SPIDriver.h"
#include "PD8544.h"
#include "snakeio.h"
#include "screenbuffer.h"
#include "Game.h"

static SnakeController controller;
static Area<21, 12> area;
static PD8544 display;
static ScreenBuffer<84, 48, PD8544> screen(&display);
static Game<ScreenBuffer<84, 48, PD8544>, Area<21, 12>, 100> game(&screen, &area, &controller);



int main(void)
{
  
	Leds::set_output();

	screen.clear();
	screen.update();	
	
    while (1) 
    {
		game.tick();
		_delay_ms(1);
    }
}

