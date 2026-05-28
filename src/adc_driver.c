/**
 * @file adc_driver.c
 *
 * @author Filip Kosecek
 *
 * @copyright Copyright (c) 2025 Filip Kosecek
 *
 * Licensed under the MIT License.
 * See LICENSE file for details.
 */

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

// The buffer used to store the values.
static volatile uint16_t values[N_VALUES];
// Flag determining the first value.
static volatile bool first = true;

// The ADC FIFO interrupt handler.
static void adc_irq_handler(void)
{
	/*
	 * The first value is discarded as it is not part of the Round robin
	 * channel multiplexing and would cause the queue to be out of sync
	 * with the color order.
	 */
	if (first) {
		first = false;
		adc_fifo_get();
		return;
	}

	// Copy the values. Interrupts are disabled during interrupt handling.
	for (size_t i = 0; i < N_VALUES; ++i)
		values[i] = adc_fifo_get();
}

/*
 * Fetch the color values atomically from the buffer.
 * Interrupts are disabled to prevent a race condition.
 */
void adc_get_atomic(uint16_t *result)
{
	uint32_t interrupt_status;

	interrupt_status = save_and_disable_interrupts();
	for (size_t i = 0; i < N_VALUES; ++i)
		result[i] = values[i];
	restore_interrupts(interrupt_status);
}

// Initialize the ADC unit.
void adc_driver_init(float clkdiv)
{
	adc_init();
	// Select the input for the first value (discarded).
	adc_select_input(3);
	// Set up the round robin mode with mask of value 7 (3 channels).
	adc_set_round_robin(ADC_INPUT_MASK);
	/*
	 * Set up the ADC queue, the interrupt is triggered when it contains
	 * at least 3 elements
	 */
	adc_fifo_setup(true, false, 3, false, true);
	adc_set_clkdiv(clkdiv);
	// Set up the interrupt handler.
	irq_set_exclusive_handler(ADC_IRQ_FIFO, adc_irq_handler);
	irq_set_priority(ADC_IRQ_FIFO, PICO_HIGHEST_IRQ_PRIORITY);
	adc_irq_set_enabled(true);
	irq_set_enabled(ADC_IRQ_FIFO, true);
	// Configure the ADC to run in a free-running mode.
	adc_run(true);
}
