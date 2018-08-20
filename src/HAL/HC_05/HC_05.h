#ifndef HC_05_HEADER
#define HC_05_HEADER

#include <inttypes.h>
#include "../../utils/data_buffer/data_buffer.h"
#include "../interrupts/interrupts.h"



	
	
class HC_05 : public Interrupts
{
	public:
	
	USART_t * usart;
	PORT_t * port;
	uint32_t baudrate;
	bool echo_mode;
	data_buffer_struct rx_data_buffer;
	data_buffer_struct tx_data_buffer;
	bool enabled;
	bool connected;
	
	HC_05(void);
	
	void isr(uint8_t);
	
	void init(void);
	bool isEnabled();
	bool isConnected();
	void enable();
	void disable();
	void init_transmision();
	bool write_byte( uint8_t );
	uint16_t write_multibyte( const char *, const uint16_t );
	uint16_t write_multibyte( const char * );
	uint8_t read_byte();
	uint16_t read_multibyte( uint8_t * , const uint16_t );
	//uint16_t read_string( char* );
	
	void isr_rxc_routine(uint8_t); // Odebrany bajt
	void isr_txc_routine(uint8_t); // Wszystko wys³ane
	void isr_dre_routine(uint8_t); // Miejsce w buforze
	void isr_port_routine(uint8_t); // przerwanie portu
};


#endif