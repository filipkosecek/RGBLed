#include <stdio.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/sync.h"

#include "adc_driver.h"

#include "picoRGB.h"
#include "define.h"

#define ADC_PIN 31
#define INPUT 0
#define CLKDIV 48000000

int main(void){
	uint32_t interrupt_status;
	uint16_t result;

	stdio_init_all();
	adc_driver_init(ADC_PIN, INPUT, CLKDIV);
	strip_init();

	while (1) {
		// wait for the interrupt
		__wfi();

		adc_get_atomic(&result);
		strip_clear();
		for (uint8_t i = 0; i < NUMLEDS; ++i) {
			strip_set_led_color(i, (uint8_t) result, 0, 100);
		}

		// atomically update the strip
		interrupt_status = save_and_disable_interrupts();
		strip_update();
		restore_interrupts(interrupt_status);
	}
	return 0;
}
