#ifndef PICORGB_H
#define PICORGB_H

#include <stdint.h>

#ifndef N_LEDS
#define N_LEDS 30
#endif

#ifndef PIO_BANK
#define PIO_BANK pio0
#endif

#ifndef SM_INDEX
#define SM_INDEX 0
#endif

#ifndef WS2812_PIN
#define WS2812_PIN 0
#endif

//#define RGBW

void ws2812_init(void);

#ifdef RGBW
int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
#else
int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue);
#endif

void ws2812_write(void);

#endif
