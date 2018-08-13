#ifndef HC_05_HEADER
#define HC_05_HEADER

#include <inttypes.h>
#include "../../utils/data_buffer/data_buffer.h"
#include "../interrupts/interrupts.h"



	#define USART_BAUDRATE	9600
	#define USART_BSEL	( (F_PER/16/USART_BAUDRATE)-1 )
	
	#define USART_BASE	USARTE0
	#define USART_PORT	PORTE
	#define USART_TX_PORT	USART_PORT
	#define USART_RX_PORT	USART_PORT
	#define USART_TX_PIN	(1<<3)
	#define USART_RX_PIN	(1<<2)
	#define BT_PORT			USART_PORT
	#define BT_EN_PIN		(1<<1)
	#define BT_STATE_PIN	(1<<0)
	
	
class HC_05 : public Interrupts
{
	public:
	
	USART_t * usart;
	PORT_t * port;
	uint32_t baudrate;
	bool echo_mode;
	data_buffer_struct rx_data_buffer;
	data_buffer_struct tx_data_buffer;
	
	void isr(uint8_t);
	
	void init(void);
	bool isEnabled();
	bool isConnected();
	void enable();
	void disable();
	void init_transmision();
	bool write_byte( uint8_t );
	uint16_t write_multibyte( uint8_t *, uint16_t );
	uint8_t read_byte();
	uint16_t read_multibyte( uint8_t * , uint16_t );
	
	void isr_rxc_routine(uint8_t); // Odebrany bajt
	void isr_txc_routine(uint8_t); // Wszystko wys³ane
	void isr_dre_routine(uint8_t); // Miejsce w buforze
	void isr_port_routine(uint8_t); // przerwanie portu
};


#endif