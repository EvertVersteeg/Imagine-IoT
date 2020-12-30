Imagine-IoT! maker files repo!
=======================================

#### Imagine IOT Nodes firmware

## 1 ATmega 328p Boards
* IMN00x Nodes (Arduino-IDE)
* Imagine Bootloader
* PCB Boardfiles (KiCad)

## 2 Nordic nRF52840 Boards
* RAK WisBlock LPWAN Module (RAK4631) (Arduino-IDE)
* TTN Payload decoder (for WisBlock)

## 3 ATtiny84 Boards
* ATTNode ATTiny84 (PlatformIO)
* Case (3D / SCAD)
* PCB Boardfiles (KiCad)

## 4 esp8266 Boards
* Wemos node (Wifi Localisation)

## 5 esp32 Boards
* P1 smart meter node (TTN Apeldoorn)

## 9 NUCLEO Boards
### NUCLEO-L476RG
* Blinky (IAR / MBED-OS)
* Alternating Flashing LEDs (IAR)
* Rotating LEDs (IAR)
* Binary Counter with LEDs (IAR)
* Random Flashing LEDs (IAR)
* Push button and LEDs (IAR)
* 7 Segment LED counter (IAR)
* LCD Displaying Text (IAR)

### NUCLEO-L053R8
* Blinky (IAR)

### NUCLEO-G071RB
* Blinky (Cube-IDE / MBED-OS)

## Wemos
* Wemos WiFi localisation
* TTN Payload decoder
 
License
=======
The files in this repository are distributed under various licenses.
Each file lists the license that applies to it, with the exception of
the bootloader binaries. These are distributed under the GPLv2, see
https://github.com/Optiboot/optiboot for the full terms and the sources
used to compile the bootloader (see the commit log of this repository to
find out the exact version used).