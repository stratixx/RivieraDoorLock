#ifndef UART_H
#define UART_H

#include <inttypes.h>
#include <avr/io.h>
#include "../../utils/return_code.h"
#include "../GPIO/gpio.h"

class UART
{
	public:
	struct UART_settings_struct
	{
		uint32_t baudrate;
	} settings;
	
	USART_t * usart;
	GPIO * gpio;
	uint8_t tx_pin;
	uint8_t rx_pin;
	const uint8_t RXC_vect_num;
	const uint8_t TXC_vect_num;
	const uint8_t DRE_vect_num;
	
	//UART(void);
	UART(USART_t*,uint8_t,uint8_t,uint8_t);
	return_code init(void);		
};


#endif