#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "../utils/return_code.h"
//#include "../Libraries/RFID/RFID.h"
#include "../Libraries/servo/servo.h"
#include "submodules/rfid/src/MFRC522.h"

class Application
{
	public:				
	//static RFID rfid;
	static SERVO servo;
	static MFRC522 rfid;
		
	static return_code launch();
};

#endif