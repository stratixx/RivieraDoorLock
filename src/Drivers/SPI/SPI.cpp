/*


*/
#include "SPI.h"

SPIClass::SPIClass( SPI_t * _spi) : spi(_spi)
{
	
}

return_code SPIClass::init()
{
	return OK;
}

void SPIClass::beginTransaction( const SPISettings settings )
{
	
}

byte SPIClass::transfer( byte data )
{
	return 0;
}

void SPIClass::endTransaction()
{
	
}