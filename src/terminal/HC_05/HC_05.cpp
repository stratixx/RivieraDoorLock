
//#include "../config/config.h"
#include <inttypes.h>
#include "UART/UART.h"
#include "HC_05.h"
#include <stdlib.h>


void HC_05::init(void)
{
	usart = &USARTE0;
	
	rx_data_buffer.tab_index = 50;
	rx_data_buffer.tab = (uint8_t*)malloc(rx_data_buffer.tab_index);
	data_buffer_clear(&rx_data_buffer);
	tx_data_buffer.tab_index = 50;
	tx_data_buffer.tab = (uint8_t*)malloc(tx_data_buffer.tab_index);
	data_buffer_clear(&tx_data_buffer);
		
	register_ISR_listener(this, USARTE0_RXC_vect_num);
	register_ISR_listener(this, USARTE0_TXC_vect_num);
	register_ISR_listener(this, USARTE0_DRE_vect_num);
	
	uart.init();
}

void HC_05::isr(uint8_t isr_vector)
{
	switch(isr_vector)
	{
		case USARTE0_RXC_vect_num:
			isr_rxc_routine(isr_vector);
			break;
		case USARTE0_TXC_vect_num:
			isr_txc_routine(isr_vector);
			break;
		case USARTE0_DRE_vect_num:
			isr_dre_routine(isr_vector);
			break;			
	}
}

bool HC_05::isEnabled()
{
	return true;
}

bool HC_05::isConnected()
{
	return true;
}

void HC_05::enable()
{
	
}

void HC_05::disable()
{
	
}

bool HC_05::write_byte( uint8_t byte )
{
	return true;
}

bool HC_05::write_multibyte( uint8_t * source, uint16_t count)
{
	return true;
}

uint8_t HC_05::read_byte()
{
	return uart.read_byte();
}

bool HC_05::read_multibyte( uint8_t * dst, uint16_t count)
{
	return uart.read_multibyte(dst,count);
}

void HC_05::isr_rxc_routine(uint8_t isr_vector)
{
	PORTA.OUTTGL = 1<<5;
	
	uint8_t data;
	data = usart->DATA;
	
	data_buffer_write( &rx_data_buffer, data );
	
	if (data==';')
	{
		while(data_buffer_ready_to_read(&rx_data_buffer))
		data_buffer_write(&tx_data_buffer,data_buffer_read(&rx_data_buffer));
		usart->CTRLA |= USART_DREINTLVL_MED_gc;
	}
	
}

void HC_05::isr_txc_routine(uint8_t isr_vector)
{
	PORTA.OUTTGL = 1<<4;
	
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	usart->CTRLA |= USART_DREINTLVL_MED_gc;
	else
	usart->CTRLA &= ~(0x03<<2); // off TXC INT
		
}

void HC_05::isr_dre_routine(uint8_t isr_vector)
{
	PORTA.OUTTGL = 1<<3;
	
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	usart->DATA = data_buffer_read(&tx_data_buffer);
	else
	usart->CTRLA &= ~(0x03<<0); // off DRE INT
	
}