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
	BIN,
	DEC,
	HEX, 
	DEC_WORD, 
	HEX_WORD
};

#define Terminal_default_print_mode Print_mode::DEC


class Terminal
{
	public:
	static bool enabled;
	static HC_05 hc_05;
	
	static return_code init();	
	
	static void print  ( const char* text=0 );
	static void println( const char* text=0 );
	
	//static void print  (byte, Print_mode=Terminal_default_print_mode);	
	//static void println(byte, Print_mode=Terminal_default_print_mode);
	static void print  (uint16_t, Print_mode=Terminal_default_print_mode);	
	static void println(uint16_t, Print_mode=Terminal_default_print_mode);
	
	static void print_return_code( const return_code );
	
	private:
	Terminal(void) {  };
};


#endif