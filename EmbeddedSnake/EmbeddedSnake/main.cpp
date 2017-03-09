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
#include "Game/Screen.h"
#include "Game/Program.h"

#include "snakeio.h"

using AREA_T   = Game::Area<Game::Field, 22, 13>;
using SCREEN_T = Game::Screen<SCREENBUFFER_T>;
using GAME_T   = Game::Game<SCREEN_T, AREA_T, 100>;

using PROGRAM_T = Game::Program<GAME_T, CONTROLLER_T, SCREEN_T>;

static CONTROLLER_T   controller;
static DISPLAY_T      display;
static SCREENBUFFER_T screenbuffer(&display);
static PROGRAM_T      program(&controller, &screenbuffer);

int main(void)
{
	program.init();
	
    while (1) 
    {
		program.tick();
		_delay_ms(1);
    }
}

