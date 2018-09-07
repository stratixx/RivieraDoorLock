
//#include "../config/config.h"
#include <inttypes.h>
#include <stdlib.h>
#include "HC_05.h"
#include "../../HAL/hal.h"
/*
HC_05::HC_05(void)
{	
	uart = 0;
	state_pin = GPIO_PIN_UNUSED;
	enable_pin = GPIO_PIN_UNUSED;
	tx_buffer_size = 0;
	rx_buffer_size = 0;
	echo_mode = false;
	enabled = false;
	connected = false;	
}*/

HC_05::HC_05(UART* uart, GPIO_pin state_pin, GPIO_pin enable_pin, uint8_t tx_buffer_size, uint8_t rx_buffer_size) : 
		uart(uart), state_pin(state_pin), enable_pin(enable_pin), tx_buffer_size(tx_buffer_size), rx_buffer_size(rx_buffer_size)
{
	state_pin_ISR_vector = 0xff;
	echo_mode = false;
	enabled = false;
	connected = false;
}

return_code HC_05::init(void)
{
	if( uart==0 ) return return_code::INIT_ERROR;
	
	state_pin_ISR_vector = get_pin_ISR_vector(state_pin, 0);
	enabled = true;
		
	rx_data_buffer.tab_index = rx_buffer_size;
	tx_data_buffer.tab_index = tx_buffer_size;
	rx_data_buffer.tab = (uint8_t*)malloc(rx_buffer_size);
	tx_data_buffer.tab = (uint8_t*)malloc(tx_buffer_size);
	data_buffer_clear(&rx_data_buffer);
	data_buffer_clear(&tx_data_buffer);
		
	register_ISR_listener(this, uart->RXC_vect_num);
	register_ISR_listener(this, uart->TXC_vect_num);
	register_ISR_listener(this, uart->DRE_vect_num);
	register_ISR_listener(this, state_pin_ISR_vector);
	
	// enable HC-05 module			
	enable();
	GPIO::pinMode(enable_pin, OUTPUT);
	// state pin
	GPIO::pinMode(state_pin, (GPIO_pin_mode)(INPUT | INT0_EN | INT_BOTHEDGES));
	//GPIO::pinMode(state_pin, INPUT);
	GPIO::digitalWrite(state_pin, HIGH);
	connected = GPIO::digitalRead(state_pin);
	//port->PIN0CTRL = PORT_OPC_PULLDOWN_gc;
		
	uart->settings.baudrate = 9600;
	
	HAL::init_uart(uart);
	return OK;
}

void HC_05::isr(uint8_t isr_vector)
{
	if( isr_vector == uart->RXC_vect_num )
		isr_rxc_routine(isr_vector);		
	else if( isr_vector == uart->TXC_vect_num )
		isr_txc_routine(isr_vector);
	else if( isr_vector == uart->DRE_vect_num )
		isr_dre_routine(isr_vector);
	else if( isr_vector == state_pin_ISR_vector )
		isr_port_routine(isr_vector);
}

bool HC_05::isEnabled()
{
	return enabled;
}

bool HC_05::isConnected()
{
	return connected;
}

void HC_05::enable()
{
	GPIO::digitalWrite(enable_pin, HIGH);
}

void HC_05::disable()
{
	GPIO::digitalWrite(enable_pin, LOW);
}

void HC_05::init_transmision()
{
	uart->init_transmision();
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
	DEBUG_CMD(GPIO::digitalWrite(GPIO_PIN_A4, TOGGLE);)
	
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
	DEBUG_CMD(GPIO::digitalWrite(GPIO_PIN_A5, TOGGLE);)
	
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	uart->usart->CTRLA |= USART_DREINTLVL_MED_gc;
	else
	uart->usart->CTRLA &= ~(0x03<<2); // off TXC INT		
}

void HC_05::isr_dre_routine(uint8_t isr_vector)
{
	//DEBUG_CMD(GPIO::digitalWrite(GPIO_PIN_A6, TOGGLE);)
	
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	uart->usart->DATA = data_buffer_read(&tx_data_buffer);
	else
	uart->usart->CTRLA &= ~(0x03<<0); // off DRE INT	
}

void HC_05::isr_port_routine(uint8_t isr_vector)
{
	DEBUG_CMD(GPIO::digitalWrite(GPIO_PIN_A6, TOGGLE);)
	
	connected = GPIO::digitalRead(state_pin);
	/*
	char hello[] = "Hello!\n\r";
	for( uint8_t n=0; hello[n]!=0; n++)
		data_buffer_write(&tx_data_buffer,hello[n]);
	init_transmision();
	*/
}