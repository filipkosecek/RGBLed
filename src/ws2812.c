#include <stdint.h>

#include <pico/stdlib.h>
#include <hardware/pio.h>

#include "ws2812.h"
#include "ws2812.pio.h"

#ifdef RGBW
#define IS_RGBW true
#else
#define IS_RGBW false
#endif

static uint32_t led_strip[N_LEDS] = {0};

void ws2812_init(void)
{
        uint offset;

        offset = pio_add_program(PIO_BANK, &ws2812_program);
        ws2812_program_init(PIO_BANK, SM_INDEX, offset, WS2812_PIN, 800000, IS_RGBW);
}

int ws2812_set_led(unsigned int i, uint8_t red, uint8_t green, uint8_t blue
#ifdef RGBW
                , uint8_t white
#endif
                )
{
        if (i >= N_LEDS)
                return -1;

#ifdef RGBW
        led_strip[i] = (uint32_t) blue          |
                       ((uint32_t) red << 8)    |
                       ((uint32_t) green << 16) |
                       ((uint32_t) white << 24);
#else
        led_strip[i] =  ((uint32_t) blue << 8) |
                        ((uint32_t) red << 16) |
                        ((uint32_t) green << 24);
#endif

        return 0;
}

void ws2812_write(void)
{
        for (unsigned int i = 0; i < N_LEDS; ++i)
                pio_sm_put_blocking(PIO_BANK, SM_INDEX, led_strip[i]);
}
