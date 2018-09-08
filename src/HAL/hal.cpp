#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal.h"

#define F_CPU 2000000UL
#include <util/delay.h>

SPIClass HAL::SPI_C(&SPIC, GPIO_PIN_C5, GPIO_PIN_C6, GPIO_PIN_C7);
SPIClass HAL::SPI_D(&SPID, GPIO_PIN_D5, GPIO_PIN_D6, GPIO_PIN_D7);
UART HAL::UART_E0(&USARTE0, USARTE0_RXC_vect_num, USARTE0_TXC_vect_num, USARTE0_DRE_vect_num, GPIO_PIN_E3, GPIO_PIN_E2);

return_code HAL::init(void)
{			
	for ( uint8_t pin=GPIO_PIN_A3; pin<=GPIO_PIN_A6; pin++ )
	{
		GPIO::digitalWrite(pin,LOW);
		GPIO::pinMode(pin, OUTPUT);
	}
	
	set_interrupts( true );
	
	return OK;
}

return_code HAL::init_uart(UART* uart)
{
	return uart->init();
}
	
void HAL::show(void)
{	
	for ( uint8_t pin=GPIO_PIN_A3; pin<=GPIO_PIN_A6; pin++ )
		for (uint8_t n=0; n<4; n++)
		{
			GPIO::digitalWrite(pin,TOGGLE);
			delay_ms(200);
			
		}
}

void HAL::set_interrupts( bool state )
{
	if( state==true )
	{
		PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
		sei();
	}
	else
		cli();
}

void HAL::bootcheck()
{
	
}

void HAL::reboot()
{
	
}

uint32_t HAL::get_clock_CPU()
{
	return F_CPU;
}
uint32_t HAL::get_clock_PER()
{
	return F_CPU;
}

void HAL::delay_ms(uint16_t delay)
{
	while( delay>0 )
	{
		delay--;
		_delay_ms(1);
	}
}

inline void HAL::delay_us( byte delay )
{
	_delay_us(delay);
}

uint32_t HAL::timestamp_ms()
{
	return 0;
}