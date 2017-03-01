/*
 * PD8544.h
 *
 * Created: 22/02/2017 11:56:15
 *  Author: KasperSK
 */ 


#ifndef PD8544_H_
#define PD8544_H_

#include <util/delay.h>
#include "SPIDriver.h"


class PD8544
{
public:
	enum class pins : uint8_t
	{
		Reset = 3,
		DataCommand = 2,
		SerialClockEnable = 4,
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

	PD8544(){
		DDRB = 0xFF;
		PORTB = 0b00001000;
		_delay_ms(10);
		PORTB = 0;
		_delay_ms(100);
		PORTB |= (1 << (uint8_t)pins::Reset) | (1 << (uint8_t)pins::SerialClockEnable);
		
		SerialClockEnable();
		SetFunction(Addressing::Vertical, InstructionSet::Extended, Powermode::Active);
		SetVop(0x50);
		SetFunction(Addressing::Vertical, InstructionSet::Basic, Powermode::Active);
		SetDisplayControl(Displaymode::Normal);
		SerialClockDisable();
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
	
	void SetYAddress(uint8_t y)
	{
		SerialClockEnable();
		Command((1 << (uint8_t)H0Commands::SetYAddress) | (y & 0b00000111));
		SerialClockDisable();
	}
	
	void SetXAddress(uint8_t x)
	{
		SerialClockEnable();
		Command((1 << (uint8_t)H0Commands::SetXAddress) | (x & 0b01111111));
		SerialClockDisable();
	}
		
	void SerialClockEnable()
	{
		PORTB &= ~(1<<(uint8_t)pins::SerialClockEnable);
	}
	
	void SerialClockDisable()
	{
		PORTB |= (1<<(uint8_t)pins::SerialClockEnable);
	}
	
	void Write(uint8_t data)
	{
		SerialClockEnable();
		Data(data);
		SerialClockDisable();
	}
	
	void Write(const uint8_t* data, uint16_t len)
	{
		SerialClockEnable();
		for(uint16_t i = 0; i < len; ++i)
		{
			Data(data[i]);
		}
		SerialClockDisable();
	}
	
protected:
private:
	void Data(uint8_t data)
	{
		PORTB |= (1 << (uint8_t)pins::DataCommand);
		SPI.Write(data);
	}
	
	void Command(uint8_t command)
	{
		PORTB &= ~(1 << (uint8_t)pins::DataCommand);
		SPI.Write(command);
	}
	
	SPIDriver<SPIDataOrder::MSB_FIRST, SPIMode::SAMPLE_RISING_SETUP_FALLING, SPIPrescale::SCK_FREQ_PRESCALE_4> SPI;
};



#endif /* PD8544_H_ */