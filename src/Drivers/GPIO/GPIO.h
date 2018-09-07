#ifndef GPIO_H
#define GPIO_H

#include "../../utils/return_code.h"
#include <avr/io.h>

#ifndef byte
	#define byte uint8_t
#endif

enum GPIO_pin_state : byte
{
	LOW = 0,
	HIGH = 1,
	TOGGLE
};

enum GPIO_pin_mode : byte
{
	INPUT		=	(0x00<<0),
	OUTPUT		=	(0x01<<0), 
	INT0_EN		=	(0x01<<1), 
	INT1_EN		=	(0x01<<2),
	INT_RISING	=	(0x01<<3),
	INT_FALLING	=	(0x02<<3),
	INT_BOTHEDGES =	(0x03<<3)
	
};

#define GPIO_PIN_MASK_BITS 3
#define GPIO_PIN_MASK ((1<<GPIO_PIN_MASK_BITS) - 1)
#define GPIO_PORT_MASK 0xf8

// Makro generujące enum-a ze wszystkimi pinami portów I/O
#define __generate_GPIO_pin__(port, offset) \
		GPIO_PIN_##port##0 = (offset), GPIO_PIN_##port##1,  GPIO_PIN_##port##2,  GPIO_PIN_##port##3,  \
		GPIO_PIN_##port##4,  GPIO_PIN_##port##5,  GPIO_PIN_##port##6,  GPIO_PIN_##port##7, 

// 5 starszych bitów koduje port, 3 młodsze bity kodują numer pinu
		
enum GPIO_pin : byte
{
	__generate_GPIO_pin__(A, 0*8) /* GPIO_A{0...7} */
	__generate_GPIO_pin__(B, 1*8) /* GPIO_B{0...7} */
	__generate_GPIO_pin__(C, 2*8) /* GPIO_C{0...7} */
	__generate_GPIO_pin__(D, 3*8) /* GPIO_D{0...7} */
	__generate_GPIO_pin__(E, 4*8) /* GPIO_E{0...7} */
	GPIO_PIN_UNUSED = 0xff
};

#undef __generate_GPIO_pin__

enum GPIO_port : byte
{
	GPIO_A = 0, GPIO_B,  GPIO_C,  GPIO_D,  GPIO_E,  GPIO_UNUSED = 0xff
};

class GPIO
{
	public:
	static return_code init(void);
	
	// ### GPIO operations ###
	// Ustawienie stanu pinu
	static void digitalWrite(byte, GPIO_pin_state);
	// Ustawienie kierunku pinu
	static void pinMode(byte, GPIO_pin_mode);
	// Odczyt stanu pinu
	static GPIO_pin_state digitalRead(byte);	
	static byte get_ISR_vector(byte, byte);
	
	private:
	GPIO() {  };
};


#endif