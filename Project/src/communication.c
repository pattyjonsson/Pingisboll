/*
 * communication.c
 *
 * Created: 2016-05
 *  Author: Patricia J�nsson och Martin Br�hagen
 */ 
#include <asf.h>
#include "communication.h"



/*
* Konfiguerar UART:en.
*/
void setupUART(void){
	pio_configure(PINS_UART_PIO, PINS_UART_TYPE, PINS_UART_MASK, PIO_DEFAULT);
	pmc_enable_periph_clk(ID_UART);
	const sam_uart_opt_t uart0_settings = { sysclk_get_cpu_hz(), CONF_UART_BAUDRATE, UART_MR_PAR_NO };
	ioport_set_pin_mode(PIO_PA8_IDX, IOPORT_MODE_PULLUP);
	uart_init(UART, &uart0_settings);
}


/*
* Anropar funktion fr�n uart.c f�r att l�sa v�rde
*/
uint8_t readValue(void){
	uint8_t value;
	uart_read(CONF_UART, &value);
	return value;
}

/*
*Returnera 1 om redo det g�r att l�sa
*/
uint32_t isReady(void){
	if(UART->UART_SR & UART_SR_RXRDY){
		return 1;
	}else{
		return 0;
	}
	 
}


/*
*Loopar tills det g�r att skicka
*/
uint32_t waitUntilReady(void){
	while(!((UART->UART_SR & UART_SR_RXRDY)>0));
	return 1;
}