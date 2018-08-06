
//#include "../config/config.h"
#include "UART/UART.h"
#include "HC_05.h"

void HC_05::init(void)
{
	uart.init();
}