/*
* PD8544.h
*
* Created: 22/02/2017 11:56:15
*  Author: KasperSK
*/


#ifndef PD8544_H_
#define PD8544_H_

#include <util/delay.h>

namespace PD8544 {
	
	template<typename T, typename U>
	T operator << (const T& ch, const U& pin)
	{
		return ch << static_cast<uint8_t>(pin);
	}


	template<typename SPIDriver>
	class Driver
	{
		public:
		
		static const uint8_t rows = 6;
		static const uint8_t columns = 84;

		enum class Pins : uint8_t
		{
			Reset = PB3,
			DataCommand = PB2,
		};

		
		enum class H1Commands : uint8_t
		{
			Bias = 4,
			Vop = 7,
			TemperatureControl = 2,
			FunctionSet = 5,
		};
		
		enum class H0Commands : uint8_t
		{
			DisplayControl = 3,
			SetYAddress = 6,
			SetXAddress = 7,
			FunctionSet = 5,
		};
		
		enum class Addressing : uint8_t
		{
			Horisontal = 0,
			Vertical = 1,
		};
		
		enum class InstructionSet : uint8_t
		{
			Basic = 0,
			Extended = 1,
		};
		
		enum class Powermode : uint8_t
		{
			Active = 0,
			Down = 1,
		};
		
		enum class Displaymode : uint8_t
		{
			Blank = 0,
			AllOn = 1,
			Normal = 2,
			Inverse = 3,
		};
		
		static const bool addressing_vertical = true;
		static const bool addressing_static = true;
		


		Driver(){
			
			SPIDriver::Init();
			
			DDRB |= ((1 << Pins::Reset) | (1 << Pins::DataCommand)) ;
			
			// Turn on Reset
			Set(Pins::Reset);
			_delay_ms(10);
			
			// Turn off Reset
			Clear(Pins::Reset);
			_delay_ms(100);
			
			// Turn on Reset
			Set(Pins::Reset);
			
			SPIDriver::Enable();
			
			//SerialClockEnable();
			SetFunction(Addressing::Vertical, InstructionSet::Extended, Powermode::Active);
			SetVop(0x50);
			SetFunction(Addressing::Vertical, InstructionSet::Basic, Powermode::Active);
			SetDisplayControl(Displaymode::Normal);
			//SerialClockDisable();
		}
		
		~Driver() {
			SPIDriver::Disable();
		}
		
		void SetBias(uint8_t bias)
		{
			Command((1 << (uint8_t)H1Commands::Bias) | (bias & 0b00000111));
		}
		
		void SetVop(uint8_t vop)
		{
			Command((1 << (uint8_t)H1Commands::Vop) | (vop & 0b01111111));
		}
		
		void SetTemperature(uint8_t temperature)
		{
			Command((1 << (uint8_t)H1Commands::TemperatureControl) | (temperature & 0b00000011));
		}
		
		void SetFunction(Addressing a, InstructionSet i, Powermode pm)
		{
			Command((1 << (uint8_t)H0Commands::FunctionSet) | ((uint8_t)pm << 2) | ((uint8_t)a << 1) | ((uint8_t)i << 0));
		}
		
		void SetDisplayControl(Displaymode mode)
		{
			uint8_t command = 0;
			switch (mode)
			{
				case Displaymode::Blank:
				command = 0;
				break;
				case Displaymode::Normal:
				command = 0b00000100;
				break;
				case Displaymode::AllOn:
				command = 0b00000001;
				break;
				case Displaymode::Inverse:
				command = 0b00000101;
				break;
			}
			Command((1 << (uint8_t)H0Commands::DisplayControl) | command);
		}
		
		void SetAddress(uint8_t x, uint8_t y)
		{
			SetXAddress(x);
			SetYAddress(y);
		}
		
		void SetYAddress(uint8_t y)
		{
			//SerialClockEnable();
			Command((1 << H0Commands::SetYAddress) | (y & 0b00000111));
			//SerialClockDisable();
		}
		
		void SetXAddress(uint8_t x)
		{
			//SerialClockEnable();
			Command((1 << (uint8_t)H0Commands::SetXAddress) | (x & 0b01111111));
			//SerialClockDisable();
		}
		
		/*
		void SerialClockEnable()
		{
			SPIDriver::Enable();
		}
		
		void SerialClockDisable()
		{
			SPIDriver::Disable();
		}
		*/
		
		void Write(uint8_t data)
		{
			
			//SerialClockEnable();
			Data(data);
			//SerialClockDisable();
		}
		
		void Write(const uint8_t* data, uint16_t len)
		{
			//SerialClockEnable();
			for(uint16_t i = 0; i < len; ++i)
			{
				Data(data[i]);
			}
			//SerialClockDisable();
		}
		
		protected:
		private:

		inline void Set(Pins pin);
		
		inline void Clear(Pins pin);

		inline void Data(uint8_t data);
		
		inline void Command(uint8_t command);
	
	};


	template<typename SPIDriver>
	void Driver<SPIDriver>::Set(Pins pin) {
		PORTB |= (1 << pin);
	}

	template<typename SPIDriver>
	void Driver<SPIDriver>::Clear(Pins pin) {
		PORTB &= ~(1 << pin);
	}

	template<typename SPIDriver>
	void Driver<SPIDriver>::Data(uint8_t data)
	{
		Set(Pins::DataCommand);
		SPIDriver::Write(data);
	}

	template<typename SPIDriver>
	void Driver<SPIDriver>::Command(uint8_t command)
	{
		Clear(Pins::DataCommand);
		SPIDriver::Write(command);
	}

}

#endif /* PD8544_H_ */