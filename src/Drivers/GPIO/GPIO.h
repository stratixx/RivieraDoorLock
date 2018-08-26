#ifndef GPIO_H
#define GPIO_H

#include "../../utils/return_code.h"
#include <avr/io.h>

class GPIO
{
	public:
	PORT_t * port;
	const uint8_t INT0_vect_num;
	const uint8_t INT1_vect_num;
	
	GPIO(PORT_t*, uint8_t, uint8_t);
	return_code init(void);
		
};


#endif