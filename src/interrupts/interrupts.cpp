#include <inttypes.h>
#include "avr/interrupt.h"
#include "interrupts.h"


/* 
	Czy przerwanie ma już swój callback
	zwraca 0 jeśli nie zarejestrowano callbacka
*/
uint8_t Interrupts::isCallbackRegistered( callbackType isr_routine_callback )
{
	if( isr_routine_callback==(&isr_NULL_routine) )
		return 0;
	else
		return 1;
}

/*
	Rejestracja callbacka dla vektora przerwania
*/
uint8_t Interrupts::registerCallback( callbackType isr_routine_callback, uint8_t vectorNumber)
{
	uint8_t result;
	callbackType* callbackPointer;
	
	callbackPointer = get_callback_by_isr_vector(vectorNumber);
	result = isCallbackRegistered(*callbackPointer);
	if ( result==0 )
		*callbackPointer = isr_routine_callback;
	
	return result;
}

/*
	Pobranie wskazania na callback dla konkretnego vectora przerwania
*/
callbackType* Interrupts::get_callback_by_isr_vector( uint8_t isr_vector )
{
	callbackType* pointer;
	
	switch(isr_vector)
	{
		case USARTE0_RXC_vect_num:
			pointer = &isr_USARTE0_RXC_routine;
			break;
		case USARTE0_TXC_vect_num:
			pointer = &isr_USARTE0_TXC_routine;			
			break;
		case USARTE0_DRE_vect_num:
			pointer = &isr_USARTE0_DRE_routine;			
			break;
		default:
			pointer = (callbackType*)&isr_NULL_routine;	
			break;
	}
	return pointer;
}

/*
	Wywołanie callbacka wskazanego przez vector przerwania
*/
void Interrupts::isr_callbacks_routine( uint8_t isr_vector )
{
	// Pobranie wskaźnika na wskaźnik callbacka i uzyskanie wskazania na funkcję callback
	callbackType callback = *get_callback_by_isr_vector(isr_vector);
	// wywołanie callback
	callback();
}

// Wywoływana w przypadku przerwania od niezarejestrowanego callbacka
void Interrupts::isr_NULL_routine(void) { }
// Odebrany bajt
void (*Interrupts::isr_USARTE0_RXC_routine)() = &Interrupts::isr_NULL_routine;
// Wszystko wysĹ‚ane
void (*Interrupts::isr_USARTE0_TXC_routine)() = &Interrupts::isr_NULL_routine;
// Miejsce w buforze
void (*Interrupts::isr_USARTE0_DRE_routine)() = &Interrupts::isr_NULL_routine;
//
void (*Interrupts::isr_INT0_routine)() = &Interrupts::isr_NULL_routine;