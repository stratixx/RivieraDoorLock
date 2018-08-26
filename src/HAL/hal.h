#ifndef HAL_H
#define HAL_H

#include "../utils/return_code.h"
#include "../Drivers/SPI/SPI.h"
#include "../Drivers/UART/uart.h"
#include "../Drivers/GPIO/gpio.h"

#ifndef byte
	#define byte uint8_t
#endif

enum Digital_state : byte
{
	LOW,
	HIGH
};

enum Digital_mode : byte
{
	INPUT,
	OUTPUT
};

class HAL
{
	public:
	static SPIClass SPI_C;
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
	
	// ### Memory operations ###
	// program memory read
	static byte pgm_read_byte(const byte*);
	
	// ### GPIO operations ###
	// Ustawienie stanu pinu
	static void digitalWrite(byte, Digital_state);
	// Ustawienie kierunku pinu
	static void pinMode(byte, Digital_mode);
	// Odczyt stanu pinu
	static Digital_state digitalRead(byte);
		
	private:
	HAL() {  };
};


#endif