#include "terminal.h"

extern const char* return_code_str[];

Terminal::Terminal(void)
{
		hal = 0;
		hc_05 = 0;
		application = 0;
}

return_code Terminal::init()
{
	if( hal!=0 )
		hc_05 = hal->get_hc_05();
	if( hal==0 || hc_05==0)
		return INIT_ERROR;
	return OK;
}
	
void Terminal::print( const char * text )
{
	if( hc_05==0 ) return;
	hc_05->write_multibyte(text);	
	hc_05->init_transmision();
}

void Terminal::println( const char * text )
{
	if( hc_05==0 ) return;
	hc_05->write_multibyte(text);
	hc_05->write_multibyte("\n\r");
	hc_05->init_transmision();
}

void Terminal::print_return_code( const return_code code )
{
	if( hc_05==0 ) return;
	hc_05->write_multibyte("__RETURN_CODE:");
	//hc_05->write_byte(code+'0');
	hc_05->write_multibyte(return_code_str[code]);
	hc_05->write_multibyte("__\n\r");
	hc_05->init_transmision();
}