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

## Build instructions
### Debian-based distros
[PicoSDK](https://github.com/raspberrypi/pico-sdk) must be installed on the
system and it must be included in the root directory of the project according
to the manual for the SDK. For building and uploading the firmware, the
following packages need to be installed (Debian-based distros):
```
sudo apt install cmake python3 build-essential gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib

```
To build the firmware:
```
mkdir build
cd build/
cmake ..
make main
```
Then upload the `main.uf2` file to the board.
