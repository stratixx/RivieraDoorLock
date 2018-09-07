/*


*/
#include "uart.h"
#include "../../HAL/hal.h"
/*
UART::UART()
{
	settings.baudrate = 0;
	usart = 0;
	gpio = 0;
	tx_pin = 0;
	rx_pin = 0;
}*/

UART::UART(USART_t * usart, uint8_t rxc_vect, uint8_t txc_vect, uint8_t dre_vect, GPIO_pin tx_pin, GPIO_pin rx_pin) : 
		usart(usart), tx_pin(tx_pin), rx_pin(rx_pin), RXC_vect_num(rxc_vect), TXC_vect_num(txc_vect), DRE_vect_num(dre_vect)
{
	settings.baudrate = 0;
}

return_code UART::init()
{
	GPIO::digitalWrite(tx_pin, HIGH);
	GPIO::pinMode(tx_pin, OUTPUT);
	GPIO::digitalWrite(rx_pin, LOW);
	GPIO::pinMode(rx_pin, INPUT);
	
	// BAUDRATE AND FRAME FORMAT	// MODE OF OPERATION
	usart->CTRLC = USART_CHSIZE_8BIT_gc;
	uint16_t bsel = ( (HAL::get_clock_PER()/16/settings.baudrate)-1 );
	usart->BAUDCTRLA = (uint8_t)(0xff&bsel);
	usart->BAUDCTRLB = 0x0f&(bsel>>8);
	//*((uint16_t*)usart->BAUDCTRLA) = ( (HAL::get_clock_PER()/16/settings.baudrate)-1 );
	// INTERRUPTS
	usart->CTRLA = USART_RXCINTLVL_MED_gc;
	// ENABLE TRANSMITTER AND RECEIVER
	usart->CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	return OK;
}

void UART::init_transmision()
{
	usart->CTRLA |= USART_DREINTLVL_MED_gc;
}