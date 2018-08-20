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
	HAL::bootcheck();
	HAL::init();
	HAL::show();
	
	// Terminal init
	#ifdef USE_TERMINAL
	Terminal::init();
	Terminal::println("Terminal init... OK");
	#endif
	
	
	// Application launch
	Application application;
	Terminal::println("Application launch... ");
	Terminal::print_return_code( application.launch() );
	Terminal::println("Application end!");
	
	//HAL::reboot();
	while(1) __asm("nop;");
};