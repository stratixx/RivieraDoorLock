#include <avr/io.h>
#include <inttypes.h>
#include "application.h"
#include "../HAL/hal.h"
#include "../Libraries/Terminal/terminal.h"

//RFID Application::rfid;
SERVO Application::servo;
MFRC522 Application::rfid(5, 4, &HAL::SPI_C, SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));

return_code Application::launch(void)
{
	Terminal::println("Application start");
	//led.init();
	//servo.init();
	//rfid.init();
	//rtc.init();
	
	uint16_t k=5;
	while (1)
	{
		if(k==0)
			break;
		k--;
		Terminal::println("Application loop");
		
		PORTA.OUTTGL = 1<<3;
		HAL::delay_ms(500);
	}
	return OK;
}