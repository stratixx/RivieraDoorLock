/*
 * RivieraDoorLock.cpp
 *
 * Created: 11.07.2018 23:24:28
 * Author : Konrad
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include "main.h"
#include "Application/application.h"
#include "HAL/hal.h"
#include "HAL/interrupts/ISR.h"

int main(void)
{
	Application application;
	HAL hal;
	
	hal.application = &application;	
	hal.bootcheck();	
	hal.init();
	hal.set_interrupts( true );
	hal.show();
	
	application.hal = &hal;
	application.init();		
	application.start();	
	
};