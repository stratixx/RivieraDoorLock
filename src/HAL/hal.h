#ifndef HAL_H
#define HAL_H

#include "hal_interface.h"
#include "../Application/application_interface.h"
#include "RFID/RFID.h"
#include "servo/servo.h"
#include "HC_05/HC_05.h"

class HAL : public HAL_interface
{
	public:
	Application_interface * application;
	RFID rfid;
	SERVO servo;
	HC_05 hc_05;
	
	void init();
	void show();
	void bootcheck();
	void set_interrupts( bool );
};


#endif