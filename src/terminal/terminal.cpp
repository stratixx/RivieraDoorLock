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
	return hc_05.isEnabled();
}

bool Terminal::write_char( char znak )
{
	return hc_05.write_byte(znak);
}

bool Terminal::write_number( uint8_t value)
{
	return false;
}

bool Terminal::write_number( uint16_t value)
{
	return false;
}

bool Terminal::write_string( char *string )
{
	return false;
}

bool Terminal::write_data( uint8_t *src, uint16_t count)
{
	return false;
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
	uint16_t tmp=0xffff;
	
	return tmp;
}

char*    Terminal::read_string(  )
{
	char * tmp=0;
	
	return tmp;
}