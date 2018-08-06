#ifndef ISR_HEADER
#define ISR_HEADER

#include "interrupts/interrupts.h"

ISR( USARTE0_RXC_vect ) // Odebrany bajt
{
	Interrupts::isr_callbacks_routine( USARTE0_RXC_vect_num );
}

ISR( USARTE0_TXC_vect ) // Wszystko wysłane
{
	Interrupts::isr_callbacks_routine( USARTE0_TXC_vect_num );

}

ISR( USARTE0_DRE_vect ) // Miejsce w buforze
{
	Interrupts::isr_callbacks_routine( USARTE0_DRE_vect_num );
}

ISR(PORTE_INT0_vect)
{
	Interrupts::isr_callbacks_routine( PORTE_INT0_vect_num);
	//select_active_terminal();
}

#endif