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
	
	rfid.PCD_Init();
	HAL::delay_ms(200);
	Terminal::print("RFID INIT: ");
	HAL::delay_ms(300);
	bool res = rfid.PCD_PerformSelfTest();
	HAL::delay_ms(300);
	Terminal::println(res,BIN);
	HAL::delay_ms(300);
	Terminal::println("---------");
	HAL::delay_ms(200);
	rfid.PCD_DumpVersionToSerial();
	HAL::delay_ms(300);
	Terminal::println("---------");
	HAL::delay_ms(200);
	Terminal::print("antena gain: ");
	rfid.PCD_AntennaOn();
	Terminal::println(rfid.PCD_GetAntennaGain(),HEX);
	uint8_t k=0;
	HAL::SPI_C.spiSettings.clock_div = SPI_CLOCK_DIV128;
	HAL::SPI_C.spiSettings.data_order = SPI_DATA_ORDER::MSBFIRST;
	HAL::SPI_C.spiSettings.mode = SPI_MODE::SPI_MODE0;
	
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
		//PORTA.OUTTGL = 1<<3;
		GPIO::digitalWrite(GPIO_PIN_A3,TOGGLE);
		
		HAL::delay_ms(500);
		
		k++;
		//if(k>5)
		//break;
	}
	return OK;
}