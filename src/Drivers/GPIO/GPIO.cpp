/*


*/
#include "GPIO.h"

GPIO::GPIO( PORT_t * _port, uint8_t INT0_vect, uint8_t INT1_vect) : port(_port), INT0_vect_num(INT0_vect), INT1_vect_num(INT1_vect)
{
	
}

return_code GPIO::init()
{
	return OK;
}
