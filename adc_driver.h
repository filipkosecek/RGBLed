#include <stdint.h>

void adc_driver_init(uint input, float clkdiv);
void adc_get_atomic(uint16_t *result);
