#ifndef HC_05_HEADER
#define HC_05_HEADER

#include "UART/UART.h"

class HC_05
{
	public:
	
	UART uart;
	
	void init(void);
	
};


#endif