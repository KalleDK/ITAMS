/*
 * EmbeddedSnake.cpp
 *
 * Created: 16/02/2017 08:55:11
 * Author : KasperSK
 */ 

#define F_CPU 3686400
#include <util/delay.h>

#include "Game/Game.h"
#include "Game/Area.h"
#include "Game/Field.h"
#include "Screen/Buffer.h"

#include "snakeio.h"

using AREA_T = Game::Area<Game::Field, 22, 13>;
using SCREENBUFFER_T = Screen::Buffer<84, 48, DISPLAY_T>;
using GAME_T = Game::Game<SCREENBUFFER_T, AREA_T, CONTROLLER_T, 100>;

static CONTROLLER_T controller;
static AREA_T area;
static DISPLAY_T display;
static SCREENBUFFER_T screen(&display);
static GAME_T game(&screen, &area, &controller);


int main(void)
{
	screen.clear();
	screen.update();	
	
    while (1) 
    {
		game.tick();
		_delay_ms(1);
    }
}

