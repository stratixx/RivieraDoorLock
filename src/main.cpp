/*
 * RivieraDoorLock.cpp
 *
 * Created: 11.07.2018 23:24:28
 * Author : Konrad
 */ 

#include <avr/io.h>
#include "main.h"
#include "Application/application.h"
#include "HAL/hal.h"
#include "Terminal/terminal.h"
#include "HAL/interrupts/ISR.h"

#define USE_TERMINAL

int main(void)
{
	// HAL init
	HAL hal;	
	hal.bootcheck();
	hal.init();
	
	// Terminal init
	Terminal terminal;
	#ifdef USE_TERMINAL
	terminal.hal = &hal;
	terminal.init();
	terminal.println("Terminal init... OK");
	#endif
	terminal.println("HAL init... OK");
	
	// Set segments references
	Application application;	
	hal.application = &application;
	hal.terminal = &terminal;
	terminal.application = &application;	
	application.hal = &hal;
	application.terminal = &terminal;
	
	// Application launch
	terminal.println("Application launch... ");
	terminal.print_return_code( application.launch() );
	terminal.println("Application end!");
	
	hal.reboot();
	while(1) __asm("nop;");
};