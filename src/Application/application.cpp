#include <avr/io.h>
#include "../config/config.h"
#include <util/delay.h>
#include "application.h"

void Application::init(void)
{
	
	for (uint16_t n=0; n<10; n++)
	{
		PORTA.OUTTGL = 0xff;
		_delay_ms(500);
	}
}

void Application::start(void)
{
	while (1)
	{
	}
}
