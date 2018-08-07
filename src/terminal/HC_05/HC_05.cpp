
//#include "../config/config.h"
#include <inttypes.h>
#include "HC_05.h"
#include <stdlib.h>


void HC_05::init(void)
{	
	rx_data_buffer.tab_index = 50;
	rx_data_buffer.tab = (uint8_t*)malloc(rx_data_buffer.tab_index);
	data_buffer_clear(&rx_data_buffer);
	tx_data_buffer.tab_index = 50;
	tx_data_buffer.tab = (uint8_t*)malloc(tx_data_buffer.tab_index);
	data_buffer_clear(&tx_data_buffer);
		
	register_ISR_listener(this, USARTE0_RXC_vect_num);
	register_ISR_listener(this, USARTE0_TXC_vect_num);
	register_ISR_listener(this, USARTE0_DRE_vect_num);
	register_ISR_listener(this, PORTE_INT0_vect_num);
	
	echo_mode = false;
	usart = &USARTE0;
	port = &PORTE;
	baudrate = 9600;
	uint32_t f_per = 2000000;
	uint16_t bsel = ( (f_per/16/baudrate)-1 );
			
	enable();
	port->OUTCLR = BT_STATE_PIN;
	port->DIRCLR = BT_STATE_PIN;
	port->PIN0CTRL = PORT_OPC_PULLDOWN_gc;
		
	port->PIN0CTRL= PORT_ISC_RISING_gc;
	port->INT0MASK= BT_STATE_PIN;
	port->INTCTRL = PORT_INT0LVL_LO_gc;
		
	port->OUTSET = USART_TX_PIN;
	port->DIRSET = USART_TX_PIN;	
	port->DIRCLR = USART_RX_PIN;
	port->OUTCLR = USART_RX_PIN;
	// BAUDRATE AND FRAME FORMAT	// MODE OF OPERATION
	usart->CTRLC = USART_CHSIZE_8BIT_gc;
	usart->BAUDCTRLA = (uint8_t)(0xff&bsel);
	usart->BAUDCTRLB = 0x0f&(bsel>>8);
	// INTERRUPTS
	usart->CTRLA = USART_RXCINTLVL_MED_gc;
	// ENABLE TRANSMITTER AND RECEIVER
	usart->CTRLB = USART_RXEN_bm | USART_TXEN_bm;
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
		case PORTE_INT0_vect_num:
			isr_port_routine(isr_vector);
			break;		
	}
}

bool HC_05::isEnabled()
{
	return port->IN&&BT_EN_PIN;
}

bool HC_05::isConnected()
{
	return port->IN&&BT_STATE_PIN;
}

void HC_05::enable()
{
	port->OUTSET = BT_EN_PIN;
	port->DIRSET = BT_EN_PIN;
}

void HC_05::disable()
{
	port->OUTCLR = BT_EN_PIN;	
}

void HC_05::init_transmision()
{
	usart->CTRLA |= USART_DREINTLVL_MED_gc;
}

bool HC_05::write_byte( uint8_t byte )
{
	if ( data_buffer_ready_to_write(&tx_data_buffer) )
		data_buffer_write(&tx_data_buffer,byte);
	else
		return false;
	return true;
}

uint16_t HC_05::write_multibyte( uint8_t * source, uint16_t count)
{
	for( uint16_t n=0; n<count; n++)
		if ( data_buffer_ready_to_write(&tx_data_buffer) )
			data_buffer_write(&tx_data_buffer,source[n]);
		else
			return count-n;
	return 0;
}

uint8_t HC_05::read_byte()
{
	return data_buffer_read(&rx_data_buffer);
}

uint16_t HC_05::read_multibyte( uint8_t * dst, uint16_t max_count)
{
	for( uint16_t n=0; n<max_count; n++)
		if ( data_buffer_ready_to_read(&rx_data_buffer) )
			dst[n] = data_buffer_read(&rx_data_buffer);
		else
			return n;
	return max_count;	
}

void HC_05::isr_rxc_routine(uint8_t isr_vector)
{
	PORTA.OUTTGL = 1<<5;
	
	uint8_t data;
	data = usart->DATA;
	
	data_buffer_write( &rx_data_buffer, data );
	
	if ( echo_mode==true && data==';')
	{
		while(data_buffer_ready_to_read(&rx_data_buffer))
			data_buffer_write(&tx_data_buffer,data_buffer_read(&rx_data_buffer));
		init_transmision();
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

void HC_05::isr_port_routine(uint8_t isr_vector)
{/*
	char hello[] = "Hello!\n\r";
	for( uint8_t n=0; hello[n]!=0; n++)
		data_buffer_write(&tx_data_buffer,hello[n]);
	init_transmision();
	*/
}