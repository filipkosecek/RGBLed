/**
 * @file adc_driver.h
 *
 * @author Filip Kosecek
 *
 * @copyright Copyright (c) 2025 Filip Kosecek
 *
 * Licensed under the MIT License.
 * See LICENSE file for details.
 */

#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>

#define N_VALUES 3
#define ADC_INPUT_MASK 7

void adc_driver_init(float clkdiv);
void adc_get_atomic(uint16_t *result);

#endif
