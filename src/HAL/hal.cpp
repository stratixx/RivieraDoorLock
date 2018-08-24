#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal.h"
#include <util/delay.h>

SPI HAL::spi_C;
UART HAL::uart_E0;
GPIO HAL::gpio_A;
GPIO HAL::gpio_B;
GPIO HAL::gpio_C;
GPIO HAL::gpio_D;
GPIO HAL::gpio_E;

return_code HAL::init(void)
{	
	PORTA.OUTSET = 0xff;
	PORTA.DIRSET = 0xff;
		
	set_interrupts( true );
	
	return OK;
}
	
void HAL::show(void)
{	
	for (uint16_t n=0; n<10; n++)
	{
		PORTA.OUTTGL = 0xff;
		_delay_ms(500);
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