/*
* TC4201.c
*
* Created: 3/3/2017 10:12:23 AM
*  Author: live
*/

#ifndef __TC4021_H__
#define __TC4021_H__

#include <util/delay.h>

//
// A CLOCK PULSE is HIGH to LOW
//
//   --------
//          |
//          |_______
//
// As the clock is HIGH as we enter we don't need to set it
// T_H is how long from we go to HIGH until the new value is
// on the DATA pin. T_SU is how long we have to stay in LOW
// for the IC to setup for the next clock.
//
// The first bit can be read without the clock, therefore
// we only need 7 clock's
//
// The safest place to read is right after we go low,
// as we are sure the data is correct there.
//

namespace TC4021 {
	
	template <typename T>
	struct Buffer {
		T data;
		
		Buffer() {
			data = 0u;
		}
		
		inline void add_bit(uint8_t bit) {
			data = data << 1 | !!bit;
		}
		
		operator uint8_t&() {
			return data;
		}
	};
	
	template <typename T, size_t REGISTER_SIZE, typename DATA, typename LATCH, typename CLOCK>
	class Driver {
		
		static const size_t size = REGISTER_SIZE;
		
		// Variables
		public:
		static const uint8_t T_rem = 45; // Min. Removal Time - From LATCH is lowered until CLOCK may be risen
		static const uint8_t T_WH  = 90; // Min. Pulse Width  - From LATCH is raised until LATCH may be lowered
		static const uint8_t T_H   = 35; // Min. Hold Time    - From CLOCK is raised until DATA can be read
		static const uint8_t T_SU  = 25; // Min. Set-up Time  - Setup time for next DATA
		protected:
		private:
		
		// Methods
		public:
		Driver() {
			init();
		}
		
		inline T read() {
			
			Buffer<T> buffer;
			
			// Start the transmission
			start_transmission();
			
			// Read all but 1 bit (as you don't need to clock for the first)
			for (auto i = 0u; i < size-1; ++i)
			{
				// Read the bit
				buffer.add_bit(DATA::read());
				
				// Go to next bit
				clock();
			}
			
			// Read the last bit
			buffer.add_bit(DATA::read());
			
			// End Transmission
			end_transmission();
			
			return buffer;
		}
		
		private:
		
		inline void init() {
			// Setting LATCH pin to OUTPUT and HIGH
			LATCH::set_output();
			LATCH::set();
			
			// Setting CLOCK pin to OUTPUT and LOW
			CLOCK::set_output();
			CLOCK::clear();
			
			// Setting DATA pin to INPUT
			DATA::set_input();
		}
		
		inline void start_transmission() {
			LATCH::clear();
			_delay_us(T_rem / 1000);
		}
		
		inline void end_transmission() {
			LATCH::set();
			_delay_us(T_WH / 1000);
		}
		
		inline void clock() {
			CLOCK::set();
			_delay_us(T_H / 1000);
			CLOCK::clear();
			_delay_us(T_SU / 1000);
		}
	
	};
}




#endif //__TC4021_H__