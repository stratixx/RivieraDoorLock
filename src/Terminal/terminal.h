#ifndef TERMINAL_H
#define TERMINAL_H

#include "../utils/return_code.h"
#include "../HAL/hal_interface.h"
#include "../Application/application_interface.h"
#include "terminal_interface.h"
#include "../HAL/HC_05/HC_05.h"

class Terminal : public Terminal_interface
{
	public:
	HAL_interface * hal;
	HC_05 * hc_05;
	Application_interface * application;
	
	Terminal(void);
	return_code init();	
	void print( const char* );
	void println( const char* );
	void print_return_code( const return_code );
};


#endif