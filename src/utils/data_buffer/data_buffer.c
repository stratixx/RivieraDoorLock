/*
 * data_buffer.cpp
 *
 * Created: 2015-05-25 15:57:31
 *  Author: Skrzatt
 */ 

// #define F_CPU 8000000UL

 #include <avr/io.h>
// #include <util/delay.h>

#include "data_buffer.h"


void data_buffer_write ( data_buffer_struct * buffer, uint8_t byte )
{
	if ( DATA_BUFFER_READY_TO_WRITE(buffer) )
	{
		buffer->tab[buffer->write_index++] = byte;
		
		if( buffer->write_index>=buffer->tab_index )
		buffer->write_index = 0;
		
		DATA_BUFFER_EMPTY_FLAG_RESET(buffer);
		DATA_BUFFER_WRITE_FLAG_SET(buffer);
		
		if( buffer->write_index==buffer->read_index )	DATA_BUFFER_FULL_FLAG_SET(buffer);
	}
}

uint8_t data_buffer_read  ( data_buffer_struct * buffer )
{
	uint8_t byte=0;
	
	if ( DATA_BUFFER_READY_TO_READ(buffer) )
	{
		byte = buffer->tab[buffer->read_index++];
		
		if( buffer->read_index>=buffer->tab_index )
		buffer->read_index = 0;
		
		DATA_BUFFER_FULL_FLAG_RESET(buffer);
		DATA_BUFFER_READ_FLAG_SET(buffer);
		
		if( buffer->read_index==buffer->write_index )	DATA_BUFFER_EMPTY_FLAG_SET(buffer);
	}
	
	return byte;
}

uint8_t data_buffer_number( data_buffer_struct * buffer )
{
	uint8_t number = 0;
	
	if		( buffer->read_index>buffer->write_index )	number = buffer->tab_index - buffer->read_index + buffer->write_index;
	else if ( buffer->read_index<buffer->write_index )	number = buffer->write_index - buffer->read_index;
	else if ( DATA_BUFFER_FULL_FLAG_IS_SET(buffer) )	number = buffer->tab_index;
	else 
		DATA_BUFFER_EMPTY_FLAG_SET(buffer);
		
	return number;
}

uint8_t	data_buffer_ready_to_read( data_buffer_struct * buffer )
{
	return DATA_BUFFER_READY_TO_READ(buffer);
}

uint8_t	data_buffer_ready_to_write( data_buffer_struct * buffer )
{
	return DATA_BUFFER_READY_TO_WRITE(buffer);
}

void	data_buffer_clear( data_buffer_struct*buffer )
{
	DATA_BUFFER_CLEAR(buffer);
}