/*
* DriverSoftware.h
*
* Created: 3/10/2017 2:55:27 PM
*  Author: live
*/


#ifndef SPI_DRIVERSOFTWARE_H_
#define SPI_DRIVERSOFTWARE_H_

namespace SPI {
	
	template <size_t REGISTER_SIZE>
	struct BufferValueType {
		using value_type = 	typename BufferValueType<REGISTER_SIZE + 1>::value_type;
	};
	
	template <>
	struct BufferValueType<8> {
		using value_type = uint8_t;
	};
	
	template <>
	struct BufferValueType<16> {
		using value_type = uint16_t;
	};
	
	template <>
	struct BufferValueType<32> {
		using value_type = uint32_t;
	};
	
	template <>
	struct BufferValueType<64> {
		using value_type = uint64_t;
	};
	
	template <size_t REGISTER_SIZE>
	struct Buffer {

		using value_type = typename BufferValueType<REGISTER_SIZE>::value_type;
		
		static const size_t size = REGISTER_SIZE;
		
		value_type data;
		
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
	
	template <typename DATA, typename LATCH, typename CLOCK>
	struct Pins {
		using latch = LATCH;
		using data  = DATA;
		using clock = CLOCK;	
	};

	template <typename BUFFER, typename PINS, uint8_t T_REM, uint8_t T_WH, uint8_t T_H, uint8_t T_SU>
	class DriverSoftware {
		
		public:
		using buffer_type = BUFFER;
		using latch_pin   = typename PINS::latch;
		using data_pin    = typename PINS::data;
		using clock_pin   = typename PINS::clock;
		using bit_type    = typename data_pin::value_type;
		
		// Variables
		
		static const size_t number_of_bits = BUFFER::size;  // Number of bits to be banged
		
		static const uint8_t T_rem = T_REM; // Min. Removal Time - From LATCH is lowered until CLOCK may be risen
		static const uint8_t T_wh  = T_WH;  // Min. Pulse Width  - From LATCH is raised until LATCH may be lowered
		static const uint8_t T_h   = T_H;   // Min. Hold Time    - From CLOCK is raised until DATA can be read
		static const uint8_t T_su  = T_SU;  // Min. Set-up Time  - Setup time for next DATA
		protected:
		private:
		
		// Methods
		public:
		DriverSoftware() {
			init();
		}
		
		inline buffer_type read() {
			
			buffer_type buffer;
			
			// Start the transmission
			start_transmission();
			
			// Read all but 1 bit (as you don't need to clock for the first)
			for (auto i = 0u; i < number_of_bits-1; ++i)
			{
				// Read the bit
				buffer.add_bit(read_bit());
				
				// Go to next bit
				pulse();
			}
			
			// Read the last bit
			buffer.add_bit(read_bit());
			
			// End Transmission
			end_transmission();
			
			return buffer;
		}
		
		private:
		
		inline void init() {
			// Setting LATCH pin to OUTPUT and HIGH
			latch_pin::set_output();
			latch_pin::set();
			
			// Setting CLOCK pin to OUTPUT and LOW
			clock_pin::set_output();
			clock_pin::clear();
			
			// Setting DATA pin to INPUT
			data_pin::set_input();
		}
		
		bit_type read_bit() {
			return data_pin::read();
		}
		
		inline void start_transmission() {
			latch_pin::clear();
			_delay_us(T_rem / 1000);
		}
		
		inline void end_transmission() {
			latch_pin::set();
			_delay_us(T_WH / 1000);
		}
		
		inline void pulse() {
			clock_pin::set();
			_delay_us(T_H / 1000);
			clock_pin::clear();
			_delay_us(T_SU / 1000);
		}
		
	};

}
#endif /* SPI_DRIVERSOFTWARE_H_ */