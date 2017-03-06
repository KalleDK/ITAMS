/*
 * snakeio.h
 *
 * Created: 3/3/2017 2:01:44 PM
 *  Author: live
 */ 

#include "ports.h"
#include "nescontroller.h"

#ifndef SNAKEIO_H_
#define SNAKEIO_H_

// NES Controller setup
using NES_DataPin = Pin<PortD, PD0>;
using NES_ClockPin = Pin<PortD, PD1>;
using NES_LatchPin = Pin<PortD, PD7>;

using SnakeController = NESController<NES_DataPin, NES_LatchPin, NES_ClockPin>;

using Leds = PortC;


#endif /* SNAKEIO_H_ */