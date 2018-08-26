#ifndef TERMINAL_H
#define TERMINAL_H

#include <inttypes.h>

#include "../../utils/return_code.h"
#include "../HC_05/HC_05.h"

#ifndef byte
	#define byte uint8_t
#endif

enum Print_mode : byte
{
	DEC = 10,
	HEX = 16
};

class Terminal
{
	public:
	static bool enabled;
	static HC_05 hc_05;
	
	static return_code init();	
	
	static void print(byte);
	static void print(byte, Print_mode);
	static void print( const char* );
	
	static void println(void);
	static void println(byte, Print_mode);
	static void println( const char* );
	static void print_return_code( const return_code );
	
	private:
	Terminal(void) {  };
};


#endif