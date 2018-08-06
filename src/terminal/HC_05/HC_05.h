#ifndef HC_05_HEADER
#define HC_05_HEADER

#include <inttypes.h>
#include "UART/UART.h"
#include "../../data_buffer/data_buffer.h"
#include "../../interrupts/interrupts.h"

class HC_05 : public Interrupts
{
	public:
	
	USART_t * usart;
	UART uart;
	data_buffer_struct rx_data_buffer;
	data_buffer_struct tx_data_buffer;
	
	void isr(uint8_t);
	
	void init(void);
	bool isEnabled();
	bool isConnected();
	void enable();
	void disable();
	bool write_byte( uint8_t byte );
	bool write_multibyte( uint8_t * source, uint16_t count);
	uint8_t read_byte();
	bool read_multibyte( uint8_t * dst, uint16_t count);
	
	void isr_rxc_routine(uint8_t); // Odebrany bajt
	void isr_txc_routine(uint8_t); // Wszystko wys³ane
	void isr_dre_routine(uint8_t); // Miejsce w buforze
};


#endif