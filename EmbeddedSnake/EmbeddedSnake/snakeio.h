/*
 * snakeio.h
 *
 * Created: 3/3/2017 2:01:44 PM
 *  Author: live
 */ 
#ifndef SNAKEIO_H_
#define SNAKEIO_H_

#include "ports.h"
using Leds = PortC;

#include "TC4021/Driver.h"
using TC4021_DataPin = Pin<PortD, PD0>;
using TC4021_ClockPin = Pin<PortD, PD1>;
using TC4021_LatchPin = Pin<PortD, PD7>;
using TC4021_T = TC4021::Driver<uint8_t, 8, TC4021_DataPin, TC4021_LatchPin, TC4021_ClockPin>;

#include "NES/Controller.h"
using CONTROLLER_T = NES::Controller<TC4021_T>;

#include "SPI/Driver.h"
using SPI_T = SPI::Driver<SPI::Order::MSB_FIRST, SPI::Mode::SAMPLE_RISING_SETUP_FALLING, SPI::Prescale::SCK_FREQ_PRESCALE_4>;

#include "PD8544/Driver.h"
using DISPLAY_T = PD8544::Driver<SPI_T>;


#endif /* SNAKEIO_H_ */