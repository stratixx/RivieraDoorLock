#ifndef RFID_HEADER
#define RFID_HEADER

#include <inttypes.h>
#include <avr/io.h>
#include "../../utils/return_code.h"
#include "../../HAL/hal.h"

// DEFINICJE
#define RFID_INTERFACE SPIC

// NAG£ÓWKI FUNKCJI

class RFID
{
	public:	
	RFID();
	return_code init(void);
	
};

#endif