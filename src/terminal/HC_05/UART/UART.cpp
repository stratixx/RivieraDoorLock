
#include "../../../config/config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../../interrupts/interrupts.h"
#include "UART.h"


void UART::init(void)
{	
	
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
		/*
		BT_PORT.OUTSET = BT_EN_PIN;
		BT_PORT.DIRSET = BT_EN_PIN;
		BT_PORT.OUTCLR = BT_STATE_PIN;
		BT_PORT.DIRCLR = BT_STATE_PIN;
		BT_PORT.PIN0CTRL = PORT_OPC_PULLDOWN_gc;
		
		select_active_terminal();
		BT_PORT.PIN0CTRL= PORT_ISC_BOTHEDGES_gc;
		BT_PORT.INT0MASK= BT_STATE_PIN;
		BT_PORT.INTCTRL = PORT_INT0LVL_LO_gc;
		*/
		USART_TX_PORT.OUTSET = USART_TX_PIN;
		USART_TX_PORT.DIRSET = USART_TX_PIN;
	
		USART_RX_PORT.DIRCLR = USART_RX_PIN;
		USART_RX_PORT.OUTCLR = USART_RX_PIN;
		// BAUDRATE AND FRAME FORMAT	// MODE OF OPERATION
		USART_BASE.CTRLC = USART_CHSIZE_8BIT_gc;
		USART_BASE.BAUDCTRLA = (uint8_t)(0xff&USART_BSEL);
		USART_BASE.BAUDCTRLB = 0x0f&(USART_BSEL>>8);
		// INTERRUPTS
		USART_BASE.CTRLA = USART_RXCINTLVL_MED_gc;// | USART_TXCINTLVL_MED_gc | USART_DREINTLVL_MED_gc;
		// ENABLE TRANSMITTER AND RECEIVER
		USART_BASE.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
		
		//USART_BASE.CTRLA |=  USART_DREINTLVL_MED_gc;
	
}


bool UART::write_byte( uint8_t byte )
{
	return true;
}

bool UART::write_multibyte( uint8_t * source, uint16_t count)
{
	return true;
}

uint8_t UART::read_byte()
{
	return 0;
}

bool UART::read_multibyte( uint8_t * dst, uint16_t count)
{
	return true;
}
