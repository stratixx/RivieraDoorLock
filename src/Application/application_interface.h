#ifndef APPLICATION_INTERFACE_HEADER
#define APPLICATION_INTERFACE_HEADER

#include "../utils/return_code.h"

class Application_interface
{
	public:		
	virtual return_code launch() { return INIT_ERROR; };
	
	
};

#endif