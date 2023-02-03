#ifndef OPENCM3_SERIAL_H
#define OPENCM3_SERIAL_H
#include "FreeRTOS.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/usart.h"
#include "queue.h"
#include "task.h"

void serial_setup(void);
void serial_print(const char *s);
#endif
