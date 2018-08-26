#ifndef Arduino_H
#define Arduino_H

/*
Plik nagłówkowy Arduino.h stworzony jako interfejs pomiędzy 
bibliotekami dedykowanymin pod Arduino, a autorską implementacją HAL.
Ścieżkę do Arduino.h należy dodać w konfiguracji projektu, 
tak, aby odwołania "#include <Arduino.h>" były poprawne
*/

#include "hal.h"
#include "Terminal/terminal.h"

#include <inttypes.h>
#include <string.h>

#define byte uint8_t

#define SPI HAL::SPI_C
#define __FlashStringHelper char
#define PROGMEM 
#define F(arg) arg
#define delay(arg) HAL::delay_ms(arg)
#define digitalWrite(arg1, arg2) HAL::digitalWrite(arg1, arg2)
#define pinMode(arg1, arg2) HAL::pinMode(arg1, arg2)
#define digitalRead(arg1) HAL::digitalRead(arg1)
#define millis() HAL::timestamp_ms()
#define delayMicroseconds(arg1) HAL::delay_us(arg1)
#define pgm_read_byte(arg1) HAL::pgm_read_byte(arg1)

#ifndef NULL
	#define NULL 0
#endif
	
// przekierowanie odwołań do Serial na Terminal
extern Terminal Serial;


#endif