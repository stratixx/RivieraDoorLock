#include <avr/io.h>
#include <inttypes.h>
#include "application.h"


Application::Application(void)
{
	hal = 0;
	terminal = 0;
}

return_code Application::launch(void)
{
	terminal->println("Application start");
	uint16_t k=5;
	while (1)
	{
		if(k==0)
		break;
		k--;
		PORTA.OUTTGL = 1<<3;
		terminal->println("Application loop");
		for( uint16_t n=0; n<0xffff; n++)
		__asm("nop; nop; nop; nop; nop; nop; nop;");
		for( uint16_t n=0; n<0xffff; n++)
		__asm("nop; nop; nop; nop; nop; nop; nop;");
		for( uint16_t n=0; n<0xffff; n++)
		__asm("nop; nop; nop; nop; nop; nop; nop;");
		for( uint16_t n=0; n<0xffff; n++)
		__asm("nop; nop; nop; nop; nop; nop; nop;");
	}
	return OK;
}