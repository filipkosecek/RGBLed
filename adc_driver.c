#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/sync.h"

static volatile uint16_t value;

static void adc_irq_handler(void)
{
	do {
		value = adc_fifo_get();
	} while (!adc_fifo_is_empty());
}

void adc_get_atomic(uint16_t *result)
{
	uint32_t interrupt_status;

	interrupt_status = save_and_disable_interrupts();
	*result = value;
	restore_interrupts(interrupt_status);
}

void adc_driver_init(uint pin, uint input, float clkdiv)
{
	adc_init();
	adc_select_input(input);
	adc_fifo_setup(true, false, 1, false, true);
	adc_set_clkdiv(clkdiv);
	irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_irq_handler);
	irq_set_priority(ADC_IRQ_FIFO, PICO_HIGHEST_IRQ_PRIORITY);
	adc_irq_set_enabled(true);
	irq_set_enabled(ADC_IRQ_FIFO, true);
	adc_run(true);
}
