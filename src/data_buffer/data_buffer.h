#ifndef Data_buffer
#define Data_buffer

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/*
BUFOR CYKLICZNY
^					write_index
XXXXXXXXXXXXXX		tab_index
^					read_index
*/


////////////////////////////////////////////////// TWORZENIE BUFORA DANYCH //////////////////////////////////////////////
//
// #define RX_BUFFER_INDEX 10 // <=255
// uint8_t	rx_data_buffer_tab[RX_BUFFER_INDEX];
// data_buffer_struct	rx_data_buffer = { rx_data_buffer_tab, RX_BUFFER_INDEX, DATA_BUFFER_EMPTY, 0, 0 };
//
// LUB
// 
// #define RX_BUFFER_INDEX 10 /* <=255 */
// DATA_BUFFER_CREATE(rx_data_buffer_tab, RX_BUFFER_INDEX, rx_data_buffer)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DATA_BUFFER_EMPTY_FLAG	0x01
#define DATA_BUFFER_FULL_FLAG	0x02
#define DATA_BUFFER_WRITE_FLAG	0x04
#define DATA_BUFFER_READ_FLAG	0x08
#define DATA_BUFFER_DONE_FLAG	0x10
#define DATA_BUFFER_CTRL		0x20	//	BIT KONTROLNY

#define DATA_BUFFER_CTRL_IS_SET(buffer)		(buffer->flag&DATA_BUFFER_CTRL)
#define DATA_BUFFER_CTRL_SET(buffer)		buffer->flag |= DATA_BUFFER_CTRL;
#define DATA_BUFFER_CTRL_RESET(buffer)		buffer->flag &= ~DATA_BUFFER_CTRL;

#define DATA_BUFFER_EMPTY_FLAG_IS_SET(buffer)	(buffer->flag&DATA_BUFFER_EMPTY_FLAG)
#define DATA_BUFFER_FULL_FLAG_IS_SET(buffer)	(buffer->flag&DATA_BUFFER_FULL_FLAG)
#define DATA_BUFFER_WRITE_FLAG_IS_SET(buffer)	(buffer->flag&DATA_BUFFER_WRITE_FLAG)
#define DATA_BUFFER_READ_FLAG_IS_SET(buffer)	(buffer->flag&DATA_BUFFER_READ_FLAG)
#define DATA_BUFFER_DONE_FLAG_IS_SET(buffer)	(buffer->flag&DATA_BUFFER_DONE_FLAG)

#define DATA_BUFFER_EMPTY_FLAG_SET(buffer)		buffer->flag |= DATA_BUFFER_EMPTY_FLAG;
#define DATA_BUFFER_FULL_FLAG_SET(buffer)		buffer->flag |= DATA_BUFFER_FULL_FLAG;
#define DATA_BUFFER_WRITE_FLAG_SET(buffer)		buffer->flag |= DATA_BUFFER_WRITE_FLAG;
#define DATA_BUFFER_READ_FLAG_SET(buffer)		buffer->flag |= DATA_BUFFER_READ_FLAG;
#define DATA_BUFFER_DONE_FLAG_SET(buffer)		buffer->flag |= DATA_BUFFER_DONE_FLAG;

#define DATA_BUFFER_EMPTY_FLAG_RESET(buffer)	buffer->flag &= ~DATA_BUFFER_EMPTY_FLAG;
#define DATA_BUFFER_FULL_FLAG_RESET(buffer)		buffer->flag &= ~DATA_BUFFER_FULL_FLAG;
#define DATA_BUFFER_WRITE_FLAG_RESET(buffer)	buffer->flag &= ~DATA_BUFFER_WRITE_FLAG;
#define DATA_BUFFER_READ_FLAG_RESET(buffer)		buffer->flag &= ~DATA_BUFFER_READ_FLAG;
#define DATA_BUFFER_DONE_FLAG_RESET(buffer)		buffer->flag &= ~DATA_BUFFER_DONE_FLAG;

#define DATA_BUFFER_READY_TO_READ(buffer)  (!DATA_BUFFER_EMPTY_FLAG_IS_SET(buffer))		/*	Czy bufor danych jest niepusty?	*/
#define DATA_BUFFER_READY_TO_WRITE(buffer) (!DATA_BUFFER_FULL_FLAG_IS_SET(buffer))		/*	Czy bufor danych jest niepe³ny?	*/


#define DATA_BUFFER_CREATE(buffer_tab_name, buffer_tab_index, buffer_name) uint8_t buffer_tab_name[buffer_tab_index]; data_buffer_struct buffer_name={buffer_tab_name,buffer_tab_index,DATA_BUFFER_EMPTY_FLAG|DATA_BUFFER_DONE_FLAG,0,0};

#define DATA_BUFFER_CLEAR(buffer) buffer->read_index=buffer->write_index; buffer->flag=DATA_BUFFER_EMPTY_FLAG;

// Struktura bufora danych
typedef struct
{
	uint8_t *tab;				// wskaŸnik do tablicy
	const uint8_t tab_index;	// index tablicy
	uint8_t flag;				// rejestr flag
	uint8_t read_index;			// index odczytu
	uint8_t write_index;		// index zapisu
} data_buffer_struct;


extern data_buffer_struct rx_data_buffer, tx_data_buffer;


void	data_buffer_write ( data_buffer_struct*, uint8_t );	// Zapis bajtu do bufora
uint8_t data_buffer_read  ( data_buffer_struct* );			// Odczyt bajtu z bufora
uint8_t data_buffer_number( data_buffer_struct* );			// Iloœæ bajtów danych w buforze
uint8_t	data_buffer_ready_to_read( data_buffer_struct* );
uint8_t	data_buffer_ready_to_write( data_buffer_struct* );
void	data_buffer_clear( data_buffer_struct* );


#ifdef __cplusplus
}
#endif // __cplusplus
#endif