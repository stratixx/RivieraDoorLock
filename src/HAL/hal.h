#ifndef HAL_H
#define HAL_H

#include "../utils/return_code.h"
#include "../Drivers/SPI/spi.h"
#include "../Drivers/UART/uart.h"
#include "../Drivers/GPIO/gpio.h"

class HAL
{
	public:
	static SPI SPI_C;
	static UART UART_E0;
	static GPIO GPIO_A;
	static GPIO GPIO_B;
	static GPIO GPIO_C;
	static GPIO GPIO_D;
	static GPIO GPIO_E;
	
	static return_code init();
	static return_code init_uart(UART*);
	//static return_code init_gpio(GPIO*);
	static void show();
	static void bootcheck();
	static void reboot();
	static void set_interrupts( bool );
	
	// clock functions
	static uint32_t get_clock_CPU();
	static uint32_t get_clock_PER();
	
	// delays
	static void delay_ms(uint16_t);
		
	private:
	HAL() {  };
};


#endif