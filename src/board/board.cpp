
#include "../config/config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "board.h"

void Board::init(void)
{	
	PORTA.OUTSET = 0xff;
	PORTA.DIRSET = 0xff;
	
	for (uint16_t n=0; n<10; n++)
	{
		PORTA.OUTTGL = 0xff;
		_delay_ms(500);
	}
}
