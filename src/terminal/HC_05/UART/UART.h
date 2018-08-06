#ifndef UART_HEADER
#define UART_HEADER

class UART
{
	public:
	
	void init(void);
	static void isr_rxc_routine(void); // Odebrany bajt
	static void isr_txc_routine(void); // Wszystko wysłane
	static void isr_dre_routine(void); // Miejsce w buforze
};

#endif