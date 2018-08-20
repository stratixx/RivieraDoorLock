#ifndef HAL_H
#define HAL_H

#include "../utils/return_code.h"
#include "RFID/RFID.h"
#include "servo/servo.h"
#include "HC_05/HC_05.h"

class HAL
{
	public:
	//static Application * application;
	static RFID rfid;
	static SERVO servo;
	static HC_05 hc_05;
	
	static return_code init(void);
	static void show(void);
	static void bootcheck();
	static void reboot();
	static void set_interrupts( bool );
		
	private:
	HAL() {  };
};


#endif