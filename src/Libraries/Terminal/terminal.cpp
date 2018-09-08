#include "terminal.h"
#include "../../HAL/hal.h"
#include <stdio.h>

HC_05 Terminal::hc_05(&HAL::UART_E0,GPIO_PIN_E0,GPIO_PIN_E1,250,50);
bool Terminal::enabled = false;

return_code Terminal::init()
{
	hc_05.init();
	enabled = hc_05.isConnected();
	return OK;
}

void Terminal::print( const char * text )
{
	enabled = hc_05.isConnected();
	if( enabled==false ) 
		return;
	if( text!=0 ) 
		hc_05.write_multibyte(text);	
	hc_05.init_transmision();
}

void Terminal::println( const char * text )
{
	enabled = hc_05.isConnected();
	if( enabled==false ) 
		return;
	if( text!=0 ) 
		hc_05.write_multibyte(text);
	hc_05.write_multibyte("\n\r");
	hc_05.init_transmision();
}

void Terminal::print(uint16_t data, Print_mode mode)
{
	char buffer[10];
	
	switch(mode)
	{
		case Print_mode::BIN:
		if( data!=0 )
			sprintf(buffer, "true");
		else
			sprintf(buffer, "false");
		break;
		case Print_mode::DEC:
		sprintf(buffer, "%3u", data);
		break;
		case Print_mode::HEX:
		sprintf(buffer, "%2.2X", data);
		break;
		case Print_mode::DEC_WORD:
		sprintf(buffer, "%5u", data);
		break;
		case Print_mode::HEX_WORD:
		sprintf(buffer, "%4.4X", data);
		break;
	}
	print(buffer);
}

void Terminal::println(uint16_t data, Print_mode mode )
{
	print(data,mode);
	println();
}

void Terminal::print_return_code( const return_code code )
{
	if( enabled==false ) return;
	hc_05.write_multibyte("__RETURN_CODE: ");
	//hc_05->write_byte(code+'0');
	hc_05.write_multibyte(return_code_str[code]);
	println();
}