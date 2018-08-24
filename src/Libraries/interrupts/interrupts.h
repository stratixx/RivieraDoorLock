#ifndef INTERRUPTS_HEADER
#define INTERRUPTS_HEADER

#include <avr/interrupt.h>
#include "../../utils/return_code.h"

/*
	Wypisanie vectorów przerwañ w isr_listeners_list
	W razie potrzeby dopisaæ kolejne
*/
enum vect_idx_type
{
	USARTE0_RXC_vect_idx,
	USARTE0_TXC_vect_idx,
	USARTE0_DRE_vect_idx,
	USARTE0_INT0_vect_idx,
	INTERRUPTS_LIST_SIZE
};


// Oko-umilacz
#define InterruptsPointer Interrupts*
//#define NULL 0

/*
	Klasa obs³uguj¹ca przypisanie vectora przerwania do obiektu klasy pochodnej
	Klasa pochodna powinna implementowaæ metodê void isr( uint8_t ), 
	a tak¿e zarejestrowaæ po¿¹dany vector przerwania
*/
class Interrupts
{
	public:
	// Konstruktor tworz¹cy jednokrotnie listê s³uchaczy
	Interrupts(void);
	// Wywo³anie obs³ugi przerwania
	static void isr_routine( uint8_t isr_vector );
	
	protected:
	static return_code register_ISR_listener( InterruptsPointer, uint8_t);
	
	private:
	static InterruptsPointer* isr_listeners_list;
	
	static InterruptsPointer* get_listener( uint8_t isr_vector );	
	virtual void isr( uint8_t ) {  };
};

#endif