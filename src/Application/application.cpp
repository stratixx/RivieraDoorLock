#include <avr/io.h>
#include <inttypes.h>
#include "application.h"
#include "../HAL/hal.h"
#include "GPIO/gpio.h"
#include "../Libraries/Terminal/terminal.h"

//RFID Application::rfid;
SERVO Application::servo;
MFRC522 Application::rfid(GPIO_PIN_C4, GPIO_PIN_C3, &HAL::SPI_C, SPISettings(SPI_CLOCK_DIV128, MSBFIRST, SPI_MODE0));

return_code Application::launch(void)
{
	Terminal::println("Application start");
	//led.init();
	//servo.init();
	//rfid.init();
	//rtc.init();
	GPIO::pinMode(GPIO_PIN_A3, OUTPUT);
	uint16_t k=0;
	while (1)
	{
		Terminal::print(k,HEX_WORD);
		Terminal::println(": Application loop");
		
		//PORTA.OUTTGL = 1<<3;
		GPIO::digitalWrite(GPIO_PIN_A3,TOGGLE);
		
		HAL::delay_ms(500);
		
		k++;
		if(k>20)
		break;
	}
	return OK;
}