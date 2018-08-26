
//#include "../config/config.h"
#include <inttypes.h>
#include <stdlib.h>
#include "HC_05.h"
#include "../../HAL/hal.h"

#define USART_BAUDRATE	9600
#define USART_BSEL	( (F_PER/16/USART_BAUDRATE)-1 )

#define USART_BASE	USARTE0
#define USART_PORT	PORTE
#define USART_TX_PORT	USART_PORT
#define USART_RX_PORT	USART_PORT
#define USART_TX_PIN	(1<<3)
#define USART_RX_PIN	(1<<2)
#define BT_PORT			USART_PORT
#define BT_EN_PIN		(1<<1)
#define BT_STATE_PIN	(1<<0)

HC_05::HC_05(void)
{	
	uart = 0;
	gpio = 0;
	state_pin = 0;
	enable_pin = 0;
	tx_buffer_size = 0;
	rx_buffer_size = 0;
	echo_mode = false;
	enabled = false;
	connected = false;	
}

void HC_05::init(void)
{
	uart = &HAL::UART_E0;
	gpio = &HAL::GPIO_E;
	state_pin = 0;
	enable_pin = 1;
	tx_buffer_size = 250;
	rx_buffer_size = 50;
	echo_mode = false;
	enabled = true;
	connected = true;
		
	rx_data_buffer.tab_index = rx_buffer_size;
	rx_data_buffer.tab = (uint8_t*)malloc(rx_buffer_size);
	data_buffer_clear(&rx_data_buffer);
	tx_data_buffer.tab_index = tx_buffer_size;
	tx_data_buffer.tab = (uint8_t*)malloc(tx_buffer_size);
	data_buffer_clear(&tx_data_buffer);
		
	register_ISR_listener(this, uart->RXC_vect_num);
	register_ISR_listener(this, uart->TXC_vect_num);
	register_ISR_listener(this, uart->DRE_vect_num);
	register_ISR_listener(this, gpio->INT0_vect_num);
				
	enable();
	PORT_t * port = gpio->port;
	port->OUTCLR = 1<<state_pin;
	port->DIRCLR = 1<<state_pin;
	port->PIN0CTRL = PORT_OPC_PULLDOWN_gc;
		
	port->PIN0CTRL= PORT_ISC_RISING_gc;
	port->INT0MASK= 1<<state_pin;
	port->INTCTRL = PORT_INT0LVL_LO_gc;
	
	port = uart->gpio->port;	
	port->OUTSET = 1<<uart->tx_pin;
	port->DIRSET = 1<<uart->tx_pin;	
	port->DIRCLR = 1<<uart->rx_pin;
	port->OUTCLR = 1<<uart->rx_pin;
	
	uart->settings.baudrate = 9600;
	
	HAL::init_uart(uart);
}

void HC_05::isr(uint8_t isr_vector)
{
	if( isr_vector == uart->RXC_vect_num )
		isr_rxc_routine(isr_vector);		
	else if( isr_vector == uart->TXC_vect_num )
		isr_txc_routine(isr_vector);
	else if( isr_vector == uart->DRE_vect_num )
		isr_dre_routine(isr_vector);
	else if( isr_vector == gpio->INT0_vect_num )
		isr_port_routine(isr_vector);
}

bool HC_05::isEnabled()
{
	//return port->IN&&BT_EN_PIN;
	return PORTE.IN&&BT_EN_PIN;
}

bool HC_05::isConnected()
{
	//return port->IN&&BT_STATE_PIN;
	return PORTE.IN&&BT_STATE_PIN;
}

void HC_05::enable()
{
	//port->OUTSET = BT_EN_PIN;
	//port->DIRSET = BT_EN_PIN;
	PORTE.OUTSET = BT_EN_PIN;
	PORTE.DIRSET = BT_EN_PIN;
}

void HC_05::disable()
{
	PORTE.OUTCLR = BT_EN_PIN;
	//port->OUTCLR = BT_EN_PIN;
}

void HC_05::init_transmision()
{
	uart->usart->CTRLA |= USART_DREINTLVL_MED_gc;
}

bool HC_05::write_byte( const uint8_t byte )
{
	if ( data_buffer_ready_to_write(&tx_data_buffer) )
		data_buffer_write(&tx_data_buffer,byte);
	else
		return false;
	return true;
}

uint16_t HC_05::write_multibyte( const char * source, uint16_t count)
{
	uint16_t n=0;
	for( ; n<count; n++)
		if ( data_buffer_ready_to_write(&tx_data_buffer) )
			data_buffer_write(&tx_data_buffer,source[n]);
		else
			break;
	return n;
}

uint16_t HC_05::write_multibyte( const char * source )
{
	uint16_t n=0;
	for( ; source[n]!=0; n++)
		if ( data_buffer_ready_to_write(&tx_data_buffer) )
			data_buffer_write(&tx_data_buffer,source[n]);
		else
			break;
	return n;
}

uint8_t HC_05::read_byte()
{
	return data_buffer_read(&rx_data_buffer);
}

uint16_t HC_05::read_multibyte( uint8_t * dst, const uint16_t max_count)
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
	PORTA.OUTTGL = 1<<4;
	
	uint8_t data;
	data = uart->usart->DATA;
	
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
	PORTA.OUTTGL = 1<<5;
	
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	uart->usart->CTRLA |= USART_DREINTLVL_MED_gc;
	else
	uart->usart->CTRLA &= ~(0x03<<2); // off TXC INT		
}

void HC_05::isr_dre_routine(uint8_t isr_vector)
{
	PORTA.OUTTGL = 1<<6;
	
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	uart->usart->DATA = data_buffer_read(&tx_data_buffer);
	else
	uart->usart->CTRLA &= ~(0x03<<0); // off DRE INT	
}

void HC_05::isr_port_routine(uint8_t isr_vector)
{/*
	char hello[] = "Hello!\n\r";
	for( uint8_t n=0; hello[n]!=0; n++)
		data_buffer_write(&tx_data_buffer,hello[n]);
	init_transmision();
	*/
}