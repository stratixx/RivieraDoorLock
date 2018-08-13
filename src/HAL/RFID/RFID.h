#ifndef RFID_HEADER
#define RFID_HEADER

#include <inttypes.h>
#include <avr/io.h>
// DEFINICJE
#define RFID_INTERFACE SPIC

// NAG£ÓWKI FUNKCJI

class RFID
{
	public:
	uint16_t number;
	
	RFID();
	
};

#endif