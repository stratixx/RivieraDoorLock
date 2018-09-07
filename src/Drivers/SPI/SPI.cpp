/*


*/
#include "SPI.h"
#include "GPIO/GPIO.h"

SPIClass::SPIClass( SPI_t * _spi, byte _MOSI_PIN, byte _MISO_PIN, byte _SCK_PIN ) : 
	spi(_spi), MOSI_PIN(_MOSI_PIN), MISO_PIN(_MISO_PIN), SCK_PIN(_SCK_PIN)
{
	
}

return_code SPIClass::init()
{
	GPIO::digitalWrite(MISO_PIN, HIGH);
	GPIO::pinMode(MISO_PIN, INPUT);
	GPIO::digitalWrite(MOSI_PIN, HIGH);
	GPIO::pinMode(MOSI_PIN, OUTPUT);
	GPIO::digitalWrite(SCK_PIN, HIGH);
	GPIO::pinMode(SCK_PIN, OUTPUT);
	
	return OK;
}

void SPIClass::beginTransaction( const SPISettings settings )
{
	register8_t tmp = 0;
	
	if(settings.clock_div&&0x04)
		tmp |= SPI_CLK2X_bm;
	
	tmp |= SPI_ENABLE_bm | settings.data_order | SPI_MASTER_bm | settings.mode | (settings.clock_div&0x03);
	
	spi->CTRL = tmp;
}

byte SPIClass::transfer( byte data )
{
	spi->DATA = data;
	while( spi->STATUS& if flag)
	return spi->DATA;
}

void SPIClass::endTransaction()
{
	spi->CTRL &= ~SPI_ENABLE_bm;
}