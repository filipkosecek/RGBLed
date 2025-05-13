# RGB lamp
The projecr uses the Raspberry Pi Pico board.
[PicoRGB library](https://github.com/ArchTonIO/PicoRGB) is used
to drive a WS2812 LED strip. Three potentiometers are connected to the
Pico board which set the level of each color.

## Structure
- `define.h` contains important constants for the library
([see the manual](https://github.com/ArchTonIO/PicoRGB))
- `PicoRGB.c` and `PicoRGB.h` files represent the library
- `ws2812.pio` belongs to the PicoRGB library and implements the protocol
responsible for driving the LED strip
- `adc_driver` files represent an interrupt-driven ADC driver which
multiplexes three ADC channels
- `main.c` - the main file
