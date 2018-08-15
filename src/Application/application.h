#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "application_conf.h"
#include "Application_interface.h"
#include "../HAL/hal_interface.h"
#include "../Terminal/terminal_interface.h"
#include "../utils/return_code.h"

class Application : public Application_interface
{
	public:				
	
	HAL_interface * hal;
	Terminal_interface * terminal;
	
	Application(void);
	return_code launch();
};

#endif