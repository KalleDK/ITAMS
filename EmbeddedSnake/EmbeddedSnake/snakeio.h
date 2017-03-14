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
using NES_Data  = Pin<PortD, PD0>;
using NES_Clock = Pin<PortD, PD2>;
using NES_Latch = Pin<PortD, PD1>;

using NES_Pins = SPI::Pins<NES_Data, NES_Latch, NES_Clock>;

using TC4021_T = TC4021::Driver<TC4021::Buffer<8>, NES_Pins>;

#include "NES/Controller.h"
using CONTROLLER_T = NES::Controller<TC4021_T>;

#include "SPI/Driver.h"
using SPI_T = SPI::Driver<SPI::Order::MSB_FIRST, SPI::SampleRisingSetupFalling, SPI::Prescale::SCK_FREQ_PRESCALE_4>;

#include "PD8544/Driver.h"
using DISPLAY_T = PD8544::Driver<SPI_T>;

#include "Screen/Buffer.h"
using SCREENBUFFER_T = Screen::Buffer<DISPLAY_T>;


#endif /* SNAKEIO_H_ */