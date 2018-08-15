#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal_conf.h"
#include "hal.h"
#include <util/delay.h>


return_code HAL::init(void)
{
	
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	
	PORTA.OUTSET = 0xff;
	PORTA.DIRSET = 0xff;
	
	//rfid.init();
	servo.init();
	hc_05.init();
	
	set_interrupts( true );
	show();
	
	return OK;
}
	
void HAL::show(void)
{	
	for (uint16_t n=0; n<10; n++)
	{
		PORTA.OUTTGL = 0xff;
		_delay_ms(500);
	}
}

void HAL::set_interrupts( bool state )
{
	if( state==true )
		sei();
	else
		cli();
}

void HAL::bootcheck()
{
	
}

void HAL::reboot()
{
	
}