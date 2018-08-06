#ifndef UART_HEADER
#define UART_HEADER

#include <inttypes.h>

class UART
{
	public:
	
	void init(void);
	bool write_byte( uint8_t byte );
	bool write_multibyte( uint8_t * source, uint16_t count);
	uint8_t read_byte();
	bool read_multibyte( uint8_t * dst, uint16_t count);
};

#endif