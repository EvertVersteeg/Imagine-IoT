# Imagine-IoT

#### Port Expander, MCP23017, 28 pins, I2C, 16 bit, IO expander:
* NUCLEO-L476RG, DIP switches, LED matrix (8x8)
* Toolchain: STM32 Cube IDE
* CUBE MX: Default board settings (80MHZ)
* Options => Debugger => ST-Link
* General Options => Device => NUCLEO-L476RG
* I2C1 port activated on PB8 (SCL) and PB9 (SDA)
* port with 10k pullup on both channels
* I2C speed: 100kHz
* I2C mode: Standard
* I2C bus clock: 80MHz
* I2C address IO expander: 0x40
