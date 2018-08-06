
#include "../../../config/config.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../../interrupts/interrupts.h"
#include "UART.h"


void UART::init(void)
{	
	Interrupts::registerCallback(&isr_rxc_routine, USARTE0_RXC_vect_num);
	Interrupts::registerCallback(&isr_txc_routine, USARTE0_TXC_vect_num);
	Interrupts::registerCallback(&isr_dre_routine, USARTE0_DRE_vect_num);
	
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

void UART::isr_rxc_routine(void)
{
	PORTA.OUTTGL = 1<<5;
	uint8_t data;
	data = USART_BASE.DATA;
	USART_BASE.DATA = data;
	/*
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	USART_BASE.CTRLA |= USART_DREINTLVL_MED_gc;
	else
	USART_BASE.CTRLA &= ~(0x03<<2); // off TXC INT
	*/	
}

void UART::isr_txc_routine(void)
{
	PORTA.OUTTGL = 1<<4;
	/*
	uint8_t data;
	data = USART_BASE.DATA;	
	
	data_buffer_write( &rx_data_buffer, data );
	
	if (data==';')
	{
		while(data_buffer_ready_to_read(&rx_data_buffer))
			data_buffer_write(&tx_data_buffer,data_buffer_read(&rx_data_buffer));
		USART_BASE.CTRLA |= USART_DREINTLVL_MED_gc;
	}
	*/	
}

void UART::isr_dre_routine(void)
{
	PORTA.OUTTGL = 1<<3;
	/*
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	USART_BASE.DATA = data_buffer_read(&tx_data_buffer);
	else
	USART_BASE.CTRLA &= ~(0x03<<0); // off DRE INT
	*/
}