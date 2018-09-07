#include <inttypes.h>
#include <stdlib.h>
#include <inttypes.h>
#include "interrupts.h"
#include "GPIO/gpio.h"

InterruptsPointer* Interrupts::isr_listeners_list = NULL;

Interrupts::Interrupts()
{
	// Jednokrotne stworzenie listy słuchaczy, wyzerowanie jej
	if ( isr_listeners_list==NULL )
	{
		isr_listeners_list = (InterruptsPointer*)malloc(sizeof(InterruptsPointer) * INTERRUPTS_LIST_SIZE);
		for( uint8_t n=0; n<INTERRUPTS_LIST_SIZE; n++)
			isr_listeners_list[n] = (InterruptsPointer)NULL;
	}
}

/*
	Rejestracja słuchacza vectora
*/
return_code Interrupts::register_ISR_listener( InterruptsPointer isr_listener, uint8_t isr_vector)
{
	InterruptsPointer* listenerPointer = get_listener(isr_vector);
	
	if ( listenerPointer!=NULL && (*listenerPointer)==NULL )
	{
		*listenerPointer = isr_listener;
		return OK;
	}
	else
		return ISR_reg_error;
}

/*
	Pobranie wskazania na słuchacza dla konkretnego vectora przerwania
*/
InterruptsPointer* Interrupts::get_listener( uint8_t isr_vector )
{
	InterruptsPointer* pointer = (InterruptsPointer*)NULL;
	
	if( isr_listeners_list!=NULL )
		switch(isr_vector)
		{
			case USARTE0_RXC_vect_num:
			pointer = &isr_listeners_list[USARTE0_RXC_vect_idx];
			break;
			case USARTE0_TXC_vect_num:
			pointer = &isr_listeners_list[USARTE0_TXC_vect_idx];
			break;
			case USARTE0_DRE_vect_num:
			pointer = &isr_listeners_list[USARTE0_DRE_vect_idx];
			break;
			case PORTA_INT0_vect_num:
			pointer = &isr_listeners_list[PORTA_INT0_vect_idx];
			break;
			case PORTA_INT1_vect_num:
			pointer = &isr_listeners_list[PORTA_INT1_vect_idx];
			break;
			case PORTB_INT0_vect_num:
			pointer = &isr_listeners_list[PORTB_INT0_vect_idx];
			break;
			case PORTB_INT1_vect_num:
			pointer = &isr_listeners_list[PORTB_INT1_vect_idx];
			break;
			case PORTC_INT0_vect_num:
			pointer = &isr_listeners_list[PORTC_INT0_vect_idx];
			break;
			case PORTC_INT1_vect_num:
			pointer = &isr_listeners_list[PORTC_INT1_vect_idx];
			break;
			case PORTD_INT0_vect_num:
			pointer = &isr_listeners_list[PORTD_INT0_vect_idx];
			break;
			case PORTD_INT1_vect_num:
			pointer = &isr_listeners_list[PORTD_INT1_vect_idx];
			break;
			case PORTE_INT0_vect_num:
			pointer = &isr_listeners_list[PORTE_INT0_vect_idx];
			break;
			case PORTE_INT1_vect_num:
			pointer = &isr_listeners_list[PORTE_INT1_vect_idx];
			break;
			case PORTF_INT0_vect_num:
			pointer = &isr_listeners_list[PORTF_INT0_vect_idx];
			break;
			case PORTF_INT1_vect_num:
			pointer = &isr_listeners_list[PORTF_INT1_vect_idx];
			break;
		}
	return pointer;
}

/*
	Wywołanie funkcji obsługi przerwania słuchacza vectora
*/
void Interrupts::isr_routine( uint8_t isr_vector )
{
	// Pobranie wskazania na słuchacza
	InterruptsPointer* listenerPointer = get_listener(isr_vector);
	if ( listenerPointer!=NULL )
	{
		InterruptsPointer listener = *listenerPointer;
		if ( listener!=NULL )
		{
			listener->isr(isr_vector);
		} 
		else
		{
			// słuchacz nie zarejestrowany
		}
	}
	else
	{
		// nieobsługiwany vector, nie ma go w switchu get_listener(uint8_t) lub niepoprawnie zainicjalizowana lista
	}
}

uint8_t Interrupts::get_pin_ISR_vector( uint8_t pin, uint8_t vector_select )
{
	return GPIO::get_ISR_vector(pin, vector_select);
}