#ifndef HAL_H
#define HAL_H

#include "../utils/return_code.h"
#include "../Drivers/SPI/SPI.h"
#include "../Drivers/UART/uart.h"
#include "../Drivers/GPIO/gpio.h"

#ifndef byte
	#define byte uint8_t
#endif

#define DEBUG_ACTIVE 1

#ifdef DEBUG_ACTIVE
	#define DEBUG_CMD(arg) arg
#else
	#define DEBUG_CMD(arg) 
#endif

//extern GPIO GPIO;

class HAL
{
	public:
	static SPIClass SPI_C;
	static SPIClass SPI_D;
	static UART UART_E0;
	
	static return_code init();
	static return_code init_uart(UART*);
	//static return_code init_gpio(GPIO*);
	static void show();
	static void bootcheck();
	static void reboot();
	static void set_interrupts( bool );
	
	// ### clock functions ###
	// get CPU clocking frequency
	static uint32_t get_clock_CPU();
	// get peripherials clocking frequency
	static uint32_t get_clock_PER();
	
	// ### time functions ###
	// delay miliseconds
	static void delay_ms(uint16_t);
	// delay us
	static void delay_us(byte);
	// timestamp miliseconds
	static uint32_t timestamp_ms();
			
	private:
	HAL() {  };
};


#endif