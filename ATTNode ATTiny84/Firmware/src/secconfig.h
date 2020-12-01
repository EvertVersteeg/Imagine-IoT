/* 
   secconfig.h - Firmware Configuration
   
   * Supported RF Modules
     #define RF_LORA  - HopeRF RFM95 LoRa Module
     #define RF_RFM69 - HopeRF RFM69(H)(C)W Module
   
   * Supported Sensors
     #define HAS_NO_SENSOR - No Sensor, just send Battery Voltage (Beacon Mode)
     #define HAS_SHT21  - Sensirion SHT21 Temperature + Humidity Sensor
     #define HAS_BME280 - Bosch BME280 Temperature + Humidity + Pressure Sensor
     #define HAS_SHT21_BRIGHTNESS  - SHT21 + Brightness via LED
     #define HAS_BME280_BRIGHTNESS - BME280 + Brightness via LED
     #define HAS_ALARM - send message when pin is triggered
     #define HAS_SHT21_ALARM - combined Sensor with SHT21 and Alarm trigger
     #define HAS_BME280_ALARM - combined Sensor with BME280 and Alarm trigger

   * LED Support
     #define LED_PIN PIN_A7 - LED is connected to ATTiny84 Pin A7 on TinyTX SMD / TinyLora

   * Brightness Measurement
     LED connected between 2 pins, switched in reverse direction for brightness measurement
     #define LED_K PIN_A7 - LED Cathode
     #define LED_A PIN_B2 - LED Anode

   * Alarm
     #define ALARM_PIN PIN_A0 - The pin defined here will trigger an immideate send if pulled low.

   * DS18B20 
     Attention!
     If you want to use DS18B20 sensors, the Onewire Library requires a clock frequency of 8MHz. 
     The value in platformio.ini must be adjusted accordingly

     DS18B20 minimum operating voltage is 3V.
     CR2032 may not be sufficient to operate the sensor.
     Use a 3.6 V power supply if necessary

     #define	DS18B20_PIN	PIN_A0 - DS18B20 Temperature sensor(s) connected on D10/ATtiny pin13  
     
     Currently 2 sensors are implemented, for more sensors either copy the lines or improve the code 
     in main.cpp
     
     If you want to turn your sensor(s) on and off connect Vdd Pin of DS18B20 with Pin defined here
     #define	DS18B20_POWER PIN_A1 - DS18B20 Power pin is connected on D9/ATtiny pin 12

    
   * Time between Measurements
     #define SLEEP_TIME 528 - Time in Seconds between Measurements. Try it out to get a good Approximation
     Examples from my Tests::
       - 528 for 10 Minute Interval with a LoRa RFM95 + BME280
       - 544 for 10 Minute Interval with a LoRa RFM95 + SHT21
     
   * See the following Examples for needed RF Module Parameters, uncomment and adapt the one fitting your Hardware
*/


// LoRa RFM95 + SHT21, LED on Pin A7

  #define RF_LORA
  #define HAS_SHT21
  #define LED_PIN PIN_A7
  #define SLEEP_TIME 544
  // Information from The Things Network, device configuration ACTIVATION METHOD: ABP, msb left
  unsigned char NwkSkey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  unsigned char AppSkey[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  unsigned char DevAddr[4] = { 0x00, 0x00, 0x00, 0x00 };


/* RFM69 + BME280, LED on Pin A7
  #define RF_RFM69
  #define HAS_BME280
  #define LED_PIN PIN_A7
  #define RFM69_NETWORKID 101 // NetworkID, 0-255, sould be the same for Node and Receiver
  #define RFM69_NODEID     29 // NodeID of this Sensor, 1-255, should be unique for every node in the same Network
  #define RFM69_GATEWAY     1 // NodeID of the Receiver, 1-255
  #define RFM69_TXPOWER    31 // Transmitting Power 0-31, see datasheet for details
  #define RFM69_ENCKEY    "0123456789ABCDEF" // AES encryption key, exactly 16 characters, if set messages will be encrypted using AES 128bit
*/

/*
// LoRa RFM95 + BME280 + Brightness Measurement
  #define RF_LORA
  #define HAS_BME280_BRIGHTNESS
  #define LED_K PIN_A7
  #define LED_A PIN_B2
  #define SLEEP_TIME 544
  */

/*
// LoRa RFM95 + Alarm
  #define RF_LORA
  #define HAS_ALARM
  #define ALARM_PIN PIN_A0
  #define LED_PIN PIN_A7
  #define SLEEP_TIME 544 
  */

 // Lora RFM95 + DS18B20
 /*
  #define RF_LORA
  #define LED_PIN PIN_A7
  #define	DS18B20_PIN	PIN_A0 // DS18B20 Temperature sensor(s) connected on D10/ATtiny pin13  
  #define	DS18B20_POWER PIN_A1  // DS18B20 Power pin(s) connected on D9/ATtiny pin 12
  #define SLEEP_TIME 544
*/
