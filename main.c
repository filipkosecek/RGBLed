#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/sync.h"

#include "adc_driver.h"

#include "picoRGB.h"
#include "define.h"

#define CLKDIV 47900000

int main(void){
	uint32_t interrupt_status;
	uint16_t result[N_VALUES];

	stdio_init_all();
	adc_driver_init(CLKDIV);
	strip_init();

	while (1) {
		// wait for the interrupt
		__wfi();

		adc_get_atomic(result);

		interrupt_status = save_and_disable_interrupts();
		strip_clear();
		for (uint8_t i = 0; i < NUMLEDS; ++i) {
			strip_set_led_color(i, (uint8_t)result[0], (uint8_t)result[1], (uint8_t)result[2]);
		}
		strip_update();
		restore_interrupts(interrupt_status);
	}
	return 0;
}
