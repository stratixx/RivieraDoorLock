/*
 * RivieraDoorLock.cpp
 *
 * Created: 11.07.2018 23:24:28
 * Author : Konrad
 */ 

#include "main.h"
#include "HAL/hal.h"
#include "Application/application.h"
#include "Libraries/Terminal/terminal.h"

#include "submodules/rfid/src/MFRC522.h"

#define USE_TERMINAL

//void SystemClock_Config(void);

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
	
	// SPI_C init
	Terminal::println("SPI_C init... ");
	Terminal::print_return_code( HAL::SPI_C.init() );
				
	// Application launch
	Terminal::println("Application launch... ");
	Terminal::print_return_code( Application::launch() );
	Terminal::println("Application end!");
	
	//HAL::reboot();
	while(1) __asm("nop;");
};