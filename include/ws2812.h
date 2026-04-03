/**
 * @file ws2812.h
 *
 * @author Filip Kosecek
 *
 * @copyright Copyright (c) 2025 Filip Kosecek
 *
 * Licensed under the MIT License.
 * See LICENSE file for details.
 */

#ifndef PICORGB_H
#define PICORGB_H

#include <stdint.h>

/** Number of LEDs on the strip. */
#ifndef N_LEDS
#define N_LEDS 30
#endif

/** The PIO bank to be used. */
#ifndef PIO_BANK
#define PIO_BANK pio0
#endif

/** The index of the state machine to be used. */
#ifndef SM_INDEX
#define SM_INDEX 0
#endif

/** The data pin to be used. */
#ifndef WS2812_PIN
#define WS2812_PIN 0
#endif

/** The flag indicating whether the strip supports white color component. */
//#define RGBW

/**
 * @brief Initialize the PIO program.
 */
void ws2812_init(void);

/**
 * @brief Set the state of the selected LED.
 *
 * @param[in] i     Index of the LED to be configured.
 * @param[in] red   Red color component.
 * @param[in] green Green color component.
 * @param[in] blue  Blue color component.
 * @param[in] white White color component (only if it is supported).
 * @return Status code, 0 on success, -1 if the LED index is out of range.
 *
 * @note The physical state of the LED is not reflected unless ws2812_write
 *       is called.
 */
#ifdef RGBW
int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
#else
int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue);
#endif

/**
 * @brief Update the LED states according to the internal state.
 */
void ws2812_write(void);

#endif
