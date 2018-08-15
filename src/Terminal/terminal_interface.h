#ifndef TERMINAL_INTERFACE_H
#define TERMINAL_INTERFACE_H

#include "../utils/return_code.h"
//#include "HC_05/HC_05.h"

class Terminal_interface
{
	public:
	
	virtual void Terminal(void) {  };
	virtual return_code init() { return INIT_ERROR; };
	virtual void print( const unsigned char* ) {  };
	virtual void println( const char* ) {  };
	virtual void print_return_code( const return_code ) {  };
};


#endif