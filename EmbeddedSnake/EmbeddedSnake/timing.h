/*
 * timing.h
 *
 * Created: 3/3/2017 12:00:48 PM
 *  Author: live
 */ 


#ifndef TIMING_H_
#define TIMING_H_

#define F_CPU 3686400
#include <util/delay.h>
#include <avr/cpufunc.h>

static inline void _delay_ns(float ns) {
	_delay_ms(ns / 1000 / 1000);
}


#endif /* TIMING_H_ */