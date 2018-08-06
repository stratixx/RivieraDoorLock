#include <avr/io.h>

#include "../config/config.h"
#include "HC_05/HC_05.h"
#include "terminal.h"

//#define RX_BUFFER_INDEX 32 /* <=255 */
//DATA_BUFFER_CREATE(rx_data_buffer_tab, RX_BUFFER_INDEX, rx_data_buffer)

//#define TX_BUFFER_INDEX 32 /* <=255 */
//DATA_BUFFER_CREATE(tx_data_buffer_tab, TX_BUFFER_INDEX, tx_data_buffer)

void Terminal::init(void)
{
	hc_05.init();
	
}