#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/sync.h"

#include "adc_driver.h"
#include "ws2812.h"

#define CLKDIV 47900000

int main(void){
	static uint16_t result[N_VALUES];
	uint32_t interrupt_status;

	// Initialize the relevant units (stdio for debugging purposes).
#ifdef DEBUG
	stdio_init_all();
#endif
	adc_driver_init(CLKDIV);
        ws2812_init();

	while (1) {
		// Wait in a low-power mode for the interrupt.
		__wfi();

		// Fetch the results.
		adc_get_atomic(result);

		// Atomically update the strip.
		interrupt_status = save_and_disable_interrupts();
		for (uint8_t i = 0; i < N_LEDS; ++i) {
			ws2812_set_led(i, (uint8_t)result[0], (uint8_t)result[1], (uint8_t)result[2]);
		}
		ws2812_write();
		restore_interrupts(interrupt_status);
	}
	return 0;
}
