#ifndef SPI_H
#define SPI_H

#include "../../utils/return_code.h"
#include <avr/io.h>

class SPI
{
	public:
	const SPI_t * spi;
	
	SPI(SPI_t*);
	return_code init(void);
		
};


#endif