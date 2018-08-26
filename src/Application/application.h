#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "../utils/return_code.h"
#include "../Libraries/RFID/RFID.h"
#include "../Libraries/servo/servo.h"

class Application
{
	public:				
	static RFID rfid;
	static SERVO servo;
		
	static return_code launch();
};

#endif