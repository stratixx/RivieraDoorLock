/*
 * RivieraDoorLock.cpp
 *
 * Created: 11.07.2018 23:24:28
 * Author : Konrad
 */ 

#include <avr/io.h>
#include "config/config.h"
#include "main.h"
#include "board/board.h"
#include "Application/application.h"
#include "servo/servo.h"
#include "terminal/terminal.h"
#include "ISR.h"

Board board;
Application application;
Terminal terminal;
SERVO servo;

int main(void)
{			
	//bootloader.check();
	board.init();
	terminal.init();
	servo.init();
	application.init();
	
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();	
	
	application.start();	
};