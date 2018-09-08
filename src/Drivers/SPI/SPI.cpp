/*


*/
#include "SPI.h"
#include "GPIO/GPIO.h"
#include "hal.h"
#include "Terminal/terminal.h"

SPIClass::SPIClass( SPI_t * _spi, byte _MOSI_PIN, byte _MISO_PIN, byte _SCK_PIN ) : 
	spi(_spi), MOSI_PIN(_MOSI_PIN), MISO_PIN(_MISO_PIN), SCK_PIN(_SCK_PIN)
{
	
}

return_code SPIClass::init()
{
	GPIO::digitalWrite(MOSI_PIN, HIGH);
	GPIO::digitalWrite(MISO_PIN, LOW);
	GPIO::digitalWrite(SCK_PIN, HIGH);
	GPIO::pinMode(MOSI_PIN, OUTPUT);
	GPIO::pinMode(MISO_PIN, INPUT);
	GPIO::pinMode(SCK_PIN, OUTPUT);
	
	return OK;
}

void SPIClass::beginTransaction( const SPISettings settings )
{		/*
	register8_t tmp = 0;
	
	if(settings.clock_div&&0x04)
		tmp |= SPI_CLK2X_bm;	
	tmp |= SPI_ENABLE_bm | settings.data_order | SPI_MASTER_bm | settings.mode | (settings.clock_div&0x03);		
	spi->CTRL = tmp;*/

	spi->CTRL =    
	SPI_ENABLE_bm|               // w³¹czenie SPI
	SPI_MASTER_bm|               // tryb master
	SPI_MODE_0_gc|               // tryb 3
	SPI_PRESCALER_DIV128_gc;      // preskaler 64
	//HAL::delay_ms(1);
	
}

byte SPIClass::transfer( byte data )
{
	spi->DATA = data;
	while( spi->STATUS==0 );// Terminal::print(".");
	data = spi->DATA;
	return data;
}

void SPIClass::endTransaction()
{
	//HAL::delay_ms(1);
	spi->CTRL &= ~SPI_ENABLE_bm;
}