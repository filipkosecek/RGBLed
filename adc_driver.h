#include <stdint.h>

#define N_VALUES 3
#define ADC_INPUT_MASK 7

void adc_driver_init(float clkdiv);
void adc_get_atomic(uint16_t *result);
