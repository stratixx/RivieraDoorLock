#ifndef HAL_H
#define HAL_H

#include "hal_interface.h"
#include "../utils/return_code.h"
#include "../Application/application_interface.h"
#include "../Terminal/terminal_interface.h"
#include "RFID/RFID.h"
#include "servo/servo.h"
#include "HC_05/HC_05.h"

class HAL : public HAL_interface
{
	public:
	Application_interface * application;
	Terminal_interface * terminal;
	RFID rfid;
	SERVO servo;
	HC_05 hc_05;
	
	return_code init();
	void show();
	void bootcheck();
	void reboot();
	void set_interrupts( bool );
	
	virtual HC_05* get_hc_05() { return &hc_05; };
	virtual SERVO* get_servo() { return &servo; };
	virtual RFID* get_RFID() { return &rfid; };
};


#endif