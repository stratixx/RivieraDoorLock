#include <avr/io.h>
#include <inttypes.h>
#include "application.h"
#include "../HAL/hal.h"
#include "GPIO/gpio.h"
#include "../Libraries/Terminal/terminal.h"
//#include "../Libraries/submodules/rfid/src/MFRC522.h"

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
	
	Terminal::println("RFID INIT: ");
	rfid.PCD_Init();
	rfid.PCD_AntennaOn();
	rfid.PCD_DumpVersionToSerial();
	Terminal::print("RFID selftest: ");
	Terminal::println(rfid.PCD_PerformSelfTest(),BIN);
	Terminal::println("RFID INIT END ");
	
	uint8_t k=0;
	byte res;
	
	while (1)
	{
		Terminal::print("0x");
		Terminal::print(k,HEX);
		
		Terminal::print(": ");
		/*
		Terminal::print(k,HEX);
		Terminal::print(" --> SPI_C --> 0x");
		HAL::SPI_C.beginTransaction(HAL::SPI_C.spiSettings);
		Terminal::println( HAL::SPI_C.transfer(k),HEX);
		HAL::SPI_C.endTransaction();
		*/
		res = rfid.PICC_IsNewCardPresent();
		Terminal::println(res,HEX);
		
		GPIO::digitalWrite(GPIO_PIN_A3,TOGGLE);
		
		HAL::delay_ms(500);
		
		k++;
		//if(k>5)
		//break;
	}
	return OK;
}