#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include "HC_05/HC_05.h"

class Terminal
{
	public:
	
	HC_05 hc_05;
	
	void init(void);
	
};


#endif