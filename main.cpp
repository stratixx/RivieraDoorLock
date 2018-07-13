/*
 * RivieraDoorLock.cpp
 *
 * Created: 11.07.2018 23:24:28
 * Author : Konrad
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"
#include <util/delay.h>
#include "src/ASF/common/services/clock/sysclk.h"
#include "src/RFID/RFID.h"
#include "src/data_buffer/data_buffer.h"


#define RX_BUFFER_INDEX 32 /* <=255 */
DATA_BUFFER_CREATE(rx_data_buffer_tab, RX_BUFFER_INDEX, rx_data_buffer)

#define TX_BUFFER_INDEX 32 /* <=255 */
DATA_BUFFER_CREATE(tx_data_buffer_tab, TX_BUFFER_INDEX, tx_data_buffer)


	 int main(void)
	{
		PORTA.OUTSET = 0xaa;
		PORTA.DIRSET = 0xff;
	
		_delay_ms(20);
		
		PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
		sei();
		sysclk_init();
	
		#define USART_BAUDRATE	9600
		#define USART_BSEL	155
	
		#define USART_BASE	USARTE0
		#define USART_TX_PORT	PORTE
		#define USART_RX_PORT	PORTE
		#define USART_TX_PIN	(1<<3)
		#define USART_RX_PIN	(1<<2)
	
		PORTE.OUTSET = 1<<1;
		PORTE.DIRSET = 1<<1;
		PORTE.OUTCLR = 1<<0;
		PORTE.DIRCLR = 1<<0;
	
		//select_active_terminal();
		PORTE.PIN0CTRL= PORT_ISC_BOTHEDGES_gc;
		PORTE.INT0MASK= 0x01;
		PORTE.INTCTRL = PORT_INT0LVL_LO_gc;
	
		PORTD.PIN0CTRL= PORT_ISC_FALLING_gc;
		PORTD.INT0MASK= 0x01;
		PORTD.INTCTRL = PORT_INT0LVL_LO_gc;
	
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
	
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	
	for (uint16_t n=0; n<10; n++)
	{
		PORTA.OUTTGL = 0xff;
		_delay_ms(500);		
	}
		while (1) 
		{
		
		};
	};
//};


class MainClass
{
	//friend void USARTE0_RXC_vect();
public:	
	uint8_t val;
	
	MainClass(void)
	{
		
		
	}
	
	~MainClass()
	{
		
	}
	
};

// void USARTE0_RXC_vect(void) __attribute__((interrupt));

ISR( USARTE0_RXC_vect ) // Odebrany bajt
{
	
	PORTA.OUTTGL = 1<<3;
	
	uint8_t data;
	data = USART_BASE.DATA;
	
	USART_BASE.DATA = data;
	/*
	data = USART_BASE.DATA;
	data_buffer_write( &rx_data_buffer, data );
	
	if (data==';')
	{
		while(data_buffer_ready_to_read(&rx_data_buffer))
			data_buffer_write(&tx_data_buffer,data_buffer_read(&rx_data_buffer));
		USART_BASE.CTRLA |= USART_DREINTLVL_MED_gc;
	}*/
}

ISR( USARTE0_TXC_vect ) // Wszystko wys�ane
{
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	USART_BASE.CTRLA |= USART_DREINTLVL_MED_gc;
	else
	USART_BASE.CTRLA &= ~(0x03<<2); // off TXC INT
}

ISR( USARTE0_DRE_vect ) // Miejsce w buforze
{
	if ( data_buffer_ready_to_read(&tx_data_buffer) )
	USART_BASE.DATA = data_buffer_read(&tx_data_buffer);
	else
	USART_BASE.CTRLA &= ~(0x03<<0); // off DRE INT
}

ISR(PORTE_INT0_vect)
{
	//select_active_terminal();
}