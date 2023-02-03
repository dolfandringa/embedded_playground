#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <opencm3_serial.h>
static QueueHandle_t serial_txq; // TX queue for UART
static void serial_task(void *args __attribute__((unused)));


static void serial_task(void *args __attribute__((unused))) {
	char ch;

	for (;;) {
		// Receive char to be TX
		if ( xQueueReceive(serial_txq,&ch,500) == pdPASS ) {
			while ( !usart_get_flag(USART1,USART_SR_TXE) )
				taskYIELD();	// Yield until ready
			usart_send(USART1,ch);
		}
	}
}

void serial_setup(void) {
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART1);
	gpio_set_mode(GPIOA,
		GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
		GPIO_USART1_TX);

	usart_set_baudrate(USART1,38400);
	usart_set_databits(USART1,8);
	usart_set_stopbits(USART1,USART_STOPBITS_1);
	usart_set_mode(USART1,USART_MODE_TX);
	usart_set_parity(USART1,USART_PARITY_NONE);
	usart_set_flow_control(USART1,USART_FLOWCONTROL_NONE);
	usart_enable(USART1);

	// Create a queue for data to transmit from UART
	serial_txq = xQueueCreate(256,sizeof(char));

	xTaskCreate(serial_task,"SERIAL",100,NULL,configMAX_PRIORITIES-1,NULL);
}



void serial_print(const char *s) {
	for ( ; *s; ++s) {
		xQueueSend(serial_txq, s ,portMAX_DELAY);
	}
}
