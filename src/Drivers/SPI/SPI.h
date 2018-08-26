#ifndef SPIClass_H
#define SPIClass_H

#include "../../utils/return_code.h"
#include <avr/io.h>

#include <inttypes.h>
#define byte uint8_t

	enum SPI_CLOCK_DIV : byte
	{
		SPI_CLOCK_DIV4
	};
	
	enum SPI_BYTE_FIRST : byte
	{
		MSBFIRST
	};
	
	enum SPI_MODE : byte
	{
		SPI_MODE0
	};
	
	struct SPISettings
	{
		SPI_CLOCK_DIV clock_div;
		SPI_BYTE_FIRST byte_first;
		SPI_MODE mode;
		
		SPISettings() {  }
		SPISettings(SPI_CLOCK_DIV _clock_div, SPI_BYTE_FIRST _byte_first, SPI_MODE _mode) :
		clock_div(_clock_div), byte_first(_byte_first), mode(_mode)
		{  }
	};
	
class SPIClass
{
	public:
	SPISettings spiSettings;
	const SPI_t * spi;
	
	SPIClass(SPI_t*);
	return_code init(void);
	void beginTransaction(const SPISettings);
	byte transfer(byte);
	void endTransaction();
		
};


#endif