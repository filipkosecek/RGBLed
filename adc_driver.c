#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "adc_driver.h"

static volatile uint16_t values[N_VALUES];

static void adc_irq_handler(void)
{
	for (size_t i = 0; i < N_VALUES; ++i)
		values[i] = adc_fifo_get();
}

void adc_get_atomic(uint16_t *result)
{
	uint32_t interrupt_status;

	interrupt_status = save_and_disable_interrupts();
	for (size_t i = 0; i < N_VALUES; ++i)
		result[i] = values[i];
	adc_fifo_drain();
	restore_interrupts(interrupt_status);
}

void adc_driver_init(float clkdiv)
{
	adc_init();
	adc_set_round_robin(ADC_INPUT_MASK);
	adc_fifo_setup(true, false, 3, false, true);
	adc_set_clkdiv(clkdiv);
	irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_irq_handler);
	irq_set_priority(ADC_IRQ_FIFO, PICO_HIGHEST_IRQ_PRIORITY);
	adc_irq_set_enabled(true);
	irq_set_enabled(ADC_IRQ_FIFO, true);
	adc_run(true);
}
