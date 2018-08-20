#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal_conf.h"
#include "hal.h"
#include <util/delay.h>

RFID HAL::rfid;
SERVO HAL::servo;
HC_05 HAL::hc_05;

return_code HAL::init(void)
{	
	PORTA.OUTSET = 0xff;
	PORTA.DIRSET = 0xff;
	
	rfid.init();
	servo.init();
	hc_05.init();
	
	set_interrupts( true );
	
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
	{
		PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
		sei();
	}
	else
		cli();
}

void HAL::bootcheck()
{
	
}

void HAL::reboot()
{
	
}