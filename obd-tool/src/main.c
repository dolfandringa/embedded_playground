/* Simple LED task demo, using timed delays:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "FreeRTOS.h"
#include "task.h"

#include <opencm3_serial.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>


#define LED_PORT GPIOC
#define LED GPIO13
#define LED_CLK RCC_GPIOC

void
vApplicationStackOverflowHook(
  TaskHandle_t pxTask __attribute((unused)),
  portCHAR *pcTaskName __attribute((unused))
) {
	for(;;);	// Loop forever here..
}

static void task1(void *args __attribute((unused))) {

	for (;;) {
		gpio_set(LED_PORT,LED);
		vTaskDelay(pdMS_TO_TICKS(500));
		gpio_clear(LED_PORT, LED);
		serial_print("Blinky\r\n");
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

int main(void) {

	rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

	rcc_periph_clock_enable(LED_CLK);
	gpio_set_mode(
		LED_PORT,
		GPIO_MODE_OUTPUT_2_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
		LED);

	serial_setup();

	xTaskCreate(task1,"LED",100,NULL,configMAX_PRIORITIES-2,NULL);
	vTaskStartScheduler();

	for (;;);
	return 0;
}

// End
