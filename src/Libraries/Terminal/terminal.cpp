#include "terminal.h"

extern const char* return_code_str[];

HC_05 Terminal::hc_05;
bool Terminal::enabled = false;

return_code Terminal::init()
{
	hc_05.init();
	enabled = true;
	return OK;
}
	
void Terminal::print( const char * text )
{
	if( enabled==false ) return;
	hc_05.write_multibyte(text);	
	hc_05.init_transmision();
}

void Terminal::println( const char * text )
{
	if( enabled==false ) return;
	hc_05.write_multibyte(text);
	hc_05.write_multibyte("\n\r");
	hc_05.init_transmision();
}

void Terminal::print_return_code( const return_code code )
{
	if( enabled==false ) return;
	hc_05.write_multibyte("__RETURN_CODE:");
	//hc_05->write_byte(code+'0');
	hc_05.write_multibyte(return_code_str[code]);
	println("__");
	hc_05.init_transmision();
}