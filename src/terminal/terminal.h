#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include "HC_05/HC_05.h"

class Terminal
{
	public:
	
	HC_05 hc_05;
	
	void init(void);	
	bool isEnabled();
	bool write_char( char );
	bool write_number( uint8_t);
	bool write_number( uint16_t );
	bool write_string( char * );
	bool write_data( uint8_t *, uint16_t );
	char     read_char(  );
	uint8_t  read_uint8_t( );
	uint16_t read_uint16_t( );
	char*    read_string(  );
	
};


#endif