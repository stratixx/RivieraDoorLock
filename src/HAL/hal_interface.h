#ifndef HAL_INTERFACE_HEADER
#define HAL_INTERFACE_HEADER

#include "../utils/return_code.h"
#include "RFID/RFID.h"
#include "servo/servo.h"
#include "HC_05/HC_05.h"

class HAL_interface
{
	public:		
	virtual HC_05* get_hc_05() { return 0; };
	virtual SERVO* get_servo() { return 0; };
	virtual RFID* get_RFID() { return 0; };
};

#endif