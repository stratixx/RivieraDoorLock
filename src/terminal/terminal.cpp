#include <avr/io.h>

#include "../config/config.h"
#include "terminal.h"
#include "HC_05/HC_05.h"


void Terminal::init(void)
{
	hc_05.init();
	
}

bool Terminal::isEnabled()
{
	return true;
}

bool Terminal::write_char( char znak )
{
	return true;
}

bool Terminal::write_uint8_t( uint8_t value)
{
	return true;
}

bool Terminal::write_uint16_t( uint16_t value)
{
	return true;
}

bool Terminal::write_string( char *string )
{
	return true;
}

char     Terminal::read_char(  )
{	
	return (char)hc_05.read_byte();
}

uint8_t  Terminal::read_uint8_t( )
{	
	return (uint8_t)hc_05.read_byte();
}

uint16_t Terminal::read_uint16_t( )
{
	uint16_t tmp;
	
	return tmp;
}

char*    Terminal::read_string(  )
{
	char * tmp;
	
	return tmp;
}