/*


*/
#include "GPIO.h"

return_code GPIO::init()
{
	return OK;
}

void GPIO::digitalWrite(byte pin, GPIO_pin_state state)
{
	byte pin_mask;
	PORT_t * port;
	
	pin_mask = 1<<(pin & GPIO_PIN_MASK); // trzy LSb koduj¹ numer pinu
	//pin &= ~0x07; // Wymazanie informacji o numerze pinu
	pin = pin>>GPIO_PIN_MASK_BITS; // zawiera teraz numer portu
	port = (&PORTB-&PORTA) * pin + &PORTA; // ustalenie adresu portu
	
	if( state==GPIO_pin_state::HIGH )
		port->OUTSET = pin_mask;
	else if( state==GPIO_pin_state::LOW )
		port->OUTCLR = pin_mask;
	else if( state==GPIO_pin_state::TOGGLE )
		port->OUTTGL = pin_mask;
}

void GPIO::pinMode(byte pin, GPIO_pin_mode mode)
{
	byte pin_number;	 // numer pinu
	byte pin_mask;		 // maska pinu
	byte port_number;	 // numer portu
	PORT_t * port;		 // adres portu
	register8_t * PINxCTRL;
	
	// dekodowanie pinu na adres portu i numer pinu
	pin_number = pin & GPIO_PIN_MASK;
	pin_mask = 1<<pin_number;
	port_number = (pin>>GPIO_PIN_MASK_BITS); 
	port = (&PORTB-&PORTA) * port_number + &PORTA; 
	PINxCTRL = (register8_t *)(((uint16_t)(&PORTA.PIN1CTRL-&PORTA.PIN0CTRL))*pin_number + (uint16_t)&port->PIN0CTRL);
	
	// INPUT/OUTPUT
	if( (mode & GPIO_pin_mode::OUTPUT)==GPIO_pin_mode::OUTPUT )
		port->DIRSET = pin_mask;
	else
		port->DIRCLR = pin_mask;
		
	// PORT INT0 ENABLE
	if( (mode & GPIO_pin_mode::INT0_EN)==GPIO_pin_mode::INT0_EN )
	{
		port->INT0MASK |= pin_mask;
		port->INTCTRL |= PORT_INT0LVL_LO_gc;
	}
	else
		port->INT0MASK &= ~pin_mask;
		
	// PORT INT1 ENABLE
	if( (mode & GPIO_pin_mode::INT1_EN)==GPIO_pin_mode::INT1_EN )
	{
		port->INT1MASK |= pin_mask;
		port->INTCTRL |= PORT_INT1LVL_LO_gc;
	}
	else
		port->INT1MASK &= ~pin_mask;	
		
	// PORT INT EDGE SELECT
	if( (mode & GPIO_pin_mode::INT_BOTHEDGES)==GPIO_pin_mode::INT_BOTHEDGES )
		*PINxCTRL = ((*PINxCTRL)&0xf8) | PORT_ISC_BOTHEDGES_gc;
	else if( (mode & GPIO_pin_mode::INT_FALLING)==GPIO_pin_mode::INT_FALLING )
		*PINxCTRL = ((*PINxCTRL)&0xf8) | PORT_ISC_FALLING_gc;
	else if( (mode & GPIO_pin_mode::INT_RISING)==GPIO_pin_mode::INT_RISING )
		*PINxCTRL = ((*PINxCTRL)&0xf8) | PORT_ISC_RISING_gc;
	else
		*PINxCTRL = ((*PINxCTRL)&0xf8) | PORT_ISC_INPUT_DISABLE_gc;
		
}

GPIO_pin_state GPIO::digitalRead(byte pin)
{
	byte pin_mask;
	PORT_t * port;
	
	pin_mask = 1<<(pin & GPIO_PIN_MASK); // trzy LSb koduj¹ numer pinu
	//pin &= ~0x07; // Wymazanie informacji o numerze pinu
	pin = pin>>GPIO_PIN_MASK_BITS; // zawiera teraz numer portu
	port = (&PORTB-&PORTA) * pin + &PORTA; // ustalenie adresu portu
	
	return (GPIO_pin_state)((port->IN)&&pin_mask);
}

byte GPIO::get_ISR_vector( byte pin, byte vector_select )
{
	byte vector = 0xff;
	
	if( vector_select>1 ) return vector;
	
	pin &= GPIO_PORT_MASK;
	pin >>= GPIO_PIN_MASK_BITS;
	
	switch(pin)
	{
		case GPIO_A:
			vector = PORTA_INT0_vect_num;
			break;
		case GPIO_B:
			vector = PORTB_INT0_vect_num;
			break;
		case GPIO_C:
			vector = PORTC_INT0_vect_num;
			break;
		case GPIO_D:
			vector = PORTD_INT0_vect_num;
			break;
		case GPIO_E:
			vector = PORTE_INT0_vect_num;
			break;
	}
	
	vector += vector_select;
	return vector;
}