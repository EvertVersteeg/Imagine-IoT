# Imagine-IoT

#### Eeprom Atmel AT24C256 Two Wire Serial EEPROM:
* NUCLEO-L476RG
* Toolchain: STM32 Cube IDE
* CUBE MX: Default board settings (80MHZ)
* Options => Debugger => ST-Link
* General Options => Device => NUCLEO-L476RG
* I2C1 port activated on PB8 (SCL) and PB9 (SDA)
* port with 10k pullup on both channels
* I2C speed: 100kHz
* I2C mode: Standard
* I2C bus clock: 80MHz
* I2C address eeprom: 0xA0
