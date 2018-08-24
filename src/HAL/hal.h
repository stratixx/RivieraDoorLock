#ifndef HAL_H
#define HAL_H

#include "../utils/return_code.h"
#include "../Drivers/SPI/spi.h"
#include "../Drivers/UART/uart.h"
#include "../Drivers/GPIO/gpio.h"

class HAL
{
	public:
	static SPI spi_C;
	static UART uart_E0;
	static GPIO gpio_A;
	static GPIO gpio_B;
	static GPIO gpio_C;
	static GPIO gpio_D;
	static GPIO gpio_E;
	
	static return_code init(void);
	static void show(void);
	static void bootcheck();
	static void reboot();
	static void set_interrupts( bool );
		
	private:
	HAL() {  };
};


#endif