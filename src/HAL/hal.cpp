#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal.h"

#define F_CPU 2000000UL
#include <util/delay.h>

SPI HAL::SPI_C(&SPIC);
UART HAL::UART_E0(&USARTE0, USARTE0_RXC_vect_num, USARTE0_TXC_vect_num, USARTE0_DRE_vect_num);
GPIO HAL::GPIO_A(&PORTA, PORTA_INT0_vect_num, PORTA_INT1_vect_num);
GPIO HAL::GPIO_B(&PORTB, PORTB_INT0_vect_num, PORTB_INT1_vect_num);
GPIO HAL::GPIO_C(&PORTC, PORTC_INT0_vect_num, PORTC_INT1_vect_num);
GPIO HAL::GPIO_D(&PORTD, PORTD_INT0_vect_num, PORTD_INT1_vect_num);
GPIO HAL::GPIO_E(&PORTE, PORTE_INT0_vect_num, PORTE_INT1_vect_num);

return_code HAL::init(void)
{
	// INIT USART_E0
	UART_E0.gpio = &GPIO_E;
	UART_E0.tx_pin = 3;
	UART_E0.rx_pin = 2;
	
	
	PORTA.OUTSET = 0xff;
	PORTA.DIRSET = 0xff;
	//uart_E0
	set_interrupts( true );
	
	return OK;
}

return_code HAL::init_uart(UART* uart)
{
	return uart->init();
}
	
void HAL::show(void)
{	
	for (uint16_t n=0; n<4; n++)
	{
		PORTA.OUTTGL = 0xff;
		_delay_ms(250);
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