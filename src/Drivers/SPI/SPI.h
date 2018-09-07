#ifndef SPIClass_H
#define SPIClass_H

#include "../../utils/return_code.h"
#include <avr/io.h>

#include <inttypes.h>
#define byte uint8_t

	enum SPI_CLOCK_DIV : byte
	{
		SPI_CLOCK_DIV4	= 0, 
		SPI_CLOCK_DIV16, 
		SPI_CLOCK_DIV64, 
		SPI_CLOCK_DIV128, 
		SPI_CLOCK_DIV2, 
		SPI_CLOCK_DIV8, 
		SPI_CLOCK_DIV32, 
	};
	
	enum SPI_DATA_ORDER : byte
	{
		MSBFIRST = (0x00<<4), 
		LSBFIRST = (0x01<<4)
	};
	
	enum SPI_MODE : byte
	{
		SPI_MODE0 = (0x00<<2), 
		SPI_MODE1 = (0x01<<2), 
		SPI_MODE2 = (0x02<<2), 
		SPI_MODE3 = (0x03<<2) 
	};
	
	struct SPISettings
	{
		SPI_CLOCK_DIV clock_div;
		SPI_DATA_ORDER data_order;
		SPI_MODE mode;
		
		SPISettings() {  }
		SPISettings(SPI_CLOCK_DIV _clock_div, SPI_DATA_ORDER _data_order, SPI_MODE _mode) :
		clock_div(_clock_div), data_order(_data_order), mode(_mode)
		{  }
	};
	
class SPIClass
{
	public:
	SPISettings spiSettings;
	SPI_t * const spi;
	const byte MOSI_PIN;
	const byte MISO_PIN;
	const byte SCK_PIN;
	
	SPIClass(SPI_t*, byte, byte, byte);
	return_code init(void);
	void beginTransaction(const SPISettings);
	byte transfer(byte);
	void endTransaction();
		
};


#endif