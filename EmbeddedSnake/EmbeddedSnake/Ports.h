/*
 * Ports.h
 *
 * Created: 3/3/2017 1:49:04 PM
 *  Author: live
 */ 


#ifndef PORTS_H_
#define PORTS_H_

#include <avr/io.h>

#define PortGenerator(value) \
struct Port##value { \
	static volatile uint8_t * const out; \
	static volatile uint8_t * const in; \
	static volatile uint8_t * const ddr; \
	\
	static void set() { \
		*out = 0xFF; \
	} \
	\
	static void clear() { \
		*out = 0x00; \
	} \
	\
	static void set_output() { \
		*ddr = 0xFF; \
	} \
	\
	static void set_input() { \
		*ddr = 0x00; \
	} \
}; \
\
volatile uint8_t * const Port##value::out = &PORT##value; \
volatile uint8_t * const Port##value::in = &PIN##value; \
volatile uint8_t * const Port##value::ddr = &DDR##value;


PortGenerator(A)
PortGenerator(B)
PortGenerator(C)
PortGenerator(D)


template<typename PORT, uint8_t NR>
struct Pin {
	static uint8_t const nr = NR;
	typedef PORT port;
	
	static uint8_t read() {
		return !!read_port();
	}
	
	static uint8_t read_port() {
		return (~(*port::in)) & (1 << nr);
	}
	
	static void set() {
		*port::out |= 1 << nr;
	}
	
	static void clear() {
		*port::out &= ~(1 << nr);
	}
	
	static void set_output() {
		*port::ddr |= 1 << nr;
	}

	static void set_input() {
		*port::ddr &= ~(1 << nr);
	}
		
};


#endif /* PORTS_H_ */