/*


*/
#include "SPI.h"
#include "GPIO/GPIO.h"
#include "Terminal/terminal.h"

SPIClass::SPIClass( SPI_t * _spi, byte _MOSI_PIN, byte _MISO_PIN, byte _SCK_PIN ) : 
	spi(_spi), MOSI_PIN(_MOSI_PIN), MISO_PIN(_MISO_PIN), SCK_PIN(_SCK_PIN)
{
	
}

return_code SPIClass::init()
{/*
	GPIO::digitalWrite(GPIO_PIN_C4, HIGH);
	GPIO::digitalWrite(GPIO_PIN_C5, HIGH);
	GPIO::digitalWrite(GPIO_PIN_C6, LOW);
	GPIO::digitalWrite(GPIO_PIN_C7, HIGH);
	GPIO::pinMode(GPIO_PIN_C4, OUTPUT);
	GPIO::pinMode(GPIO_PIN_C5, OUTPUT);
	GPIO::pinMode(GPIO_PIN_C6, INPUT);
	GPIO::pinMode(GPIO_PIN_C7, OUTPUT);
	*/

	PORTC.OUTSET = PIN4_bm | PIN5_bm | PIN7_bm;
	PORTC.OUTCLR = PIN6_bm;
	PORTC.DIRSET = PIN4_bm | PIN5_bm | PIN7_bm;
	PORTC.DIRCLR = PIN6_bm;

	SPIC.CTRL       =    
	SPI_ENABLE_bm|               // w³¹czenie SPI
	SPI_MASTER_bm|               // tryb master
	SPI_MODE_3_gc|               // tryb 3
	SPI_PRESCALER_DIV128_gc;      // preskaler 64
	
	return OK;
}

void SPIClass::beginTransaction( const SPISettings settings )
{/*
	GPIO::digitalWrite(MOSI_PIN, HIGH);
	GPIO::pinMode(MOSI_PIN, OUTPUT);
	GPIO::digitalWrite(MISO_PIN, HIGH);
	GPIO::pinMode(MISO_PIN, INPUT);
	GPIO::digitalWrite(SCK_PIN, HIGH);
	GPIO::pinMode(SCK_PIN, OUTPUT);*/
		/*
	register8_t tmp = 0;
	
	if(settings.clock_div&&0x04)
		tmp |= SPI_CLK2X_bm;
	
	tmp |= SPI_ENABLE_bm | settings.data_order | SPI_MASTER_bm | settings.mode | (settings.clock_div&0x03);
	
	tmp = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV128_gc;
	
	spi->CTRL = tmp;
	
	SPIC.CTRL       =    SPI_CLK2X_bm|
	SPI_ENABLE_bm|               // w³¹czenie SPI
	SPI_MASTER_bm|               // tryb master
	SPI_MODE_3_gc|               // tryb 3
	SPI_PRESCALER_DIV4_gc;      // preskaler 64
	*/
}

byte SPIClass::transfer( byte data )
{
	//Terminal::print("(preSTATUS=");
	//Terminal::print(SPIC.STATUS,HEX);
	//Terminal::print(")");
	SPIC.DATA = data;
	//Terminal::print("(postSTATUS=");
	//Terminal::print(SPIC.STATUS,HEX);
	//Terminal::print(")");
	while( SPIC.STATUS==0 );// Terminal::print(".");
	data = SPIC.DATA;
	return data;
}

void SPIClass::endTransaction()
{
	//spi->CTRL &= ~SPI_ENABLE_bm;
}