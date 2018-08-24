#include <avr/interrupt.h>
#include "ISR.h"
//#include "../../HAL/hal.h"
#include "../../Libraries/interrupts/interrupts.h"

// Mostek pomiedzy standardowym ISR a klasą HAL
#define REGISTER_ISR(isr_vector) \
ISR( isr_vector )\
{\
	Interrupts::isr_routine( isr_vector ## _num );\
}

REGISTER_ISR( USARTE0_RXC_vect )
REGISTER_ISR( USARTE0_TXC_vect )
REGISTER_ISR( USARTE0_DRE_vect )
REGISTER_ISR( PORTE_INT0_vect )