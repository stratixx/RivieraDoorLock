#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "application_conf.h"
#include "Application_interface.h"
#include "../HAL/hal_interface.h"

class Application : public Application_interface
{
	public:				
	
	HAL_interface * hal;
	
	void init();
	void start(void);
};

#endif