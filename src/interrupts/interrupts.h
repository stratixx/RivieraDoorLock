#ifndef INTERRUPTS_HEADER
#define INTERRUPTS_HEADER


typedef void(*callbackType)();

class Interrupts
{
	public:
	static uint8_t registerCallback( callbackType, uint8_t vectorNumber);
	static uint8_t isCallbackRegistered( callbackType );
	static callbackType* get_callback_by_isr_vector( uint8_t isr_vector );
	static void isr_callbacks_routine( uint8_t isr_vector );
	
	// domyślna procedura
	static void isr_NULL_routine();
	// Odebrany bajt
	static void (*isr_USARTE0_RXC_routine)();	
	// Wszystko wysĹ‚ane
	static void (*isr_USARTE0_TXC_routine)();
	// Miejsce w buforze
	static void (*isr_USARTE0_DRE_routine)();
	// 
	static void (*isr_INT0_routine)();
};

#endif