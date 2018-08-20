#ifndef TERMINAL_H
#define TERMINAL_H

#include <inttypes.h>

#include "../utils/return_code.h"
#include "../HAL/hal.h"

class Terminal
{
	public:
	static bool enabled;
	
	static return_code init();	
	static void print( const char* );
	static void println( const char* );
	static void print_return_code( const return_code );
	
	private:
	Terminal(void) {  };
};


#endif