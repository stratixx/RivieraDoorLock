/*
 * RivieraDoorLock.cpp
 *
 * Created: 11.07.2018 23:24:28
 * Author : Konrad
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "config/config.h"
#include "main.h"
#include <util/delay.h>
#include "Application/application.h"
//#include "data_buffer/data_buffer.h"
//#include "HC-05/HC_05.h"
//#include "RFID/RFID.h"

#include "servo/servo.h"
#include "terminal/terminal.h"
#include "ISR.h"

Application application;
Terminal terminal;
SERVO servo;



int main(void)
{			
	
	PORTA.OUTSET = 0xff;
	PORTA.DIRSET = 0xff;
	_delay_ms(20);
	//bootloader.check();
	//board.init();
	terminal.init();
	servo.init();
	application.init();
	
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	
	
	application.start();	
};