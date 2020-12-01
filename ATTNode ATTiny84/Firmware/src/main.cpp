/*
  main.cpp - ATTNode / TinyTX Firmware
  Copyright (c) 2019-2020, Stefan Brand
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <tinySPI.h>

// secconfig.h Configures RF Module, TTN Keys / RF Networks and used Sensor
#include "secconfig.h"

// Create needed Variables and Objects for RF Module
#ifdef RF_LORA
  // Include LoRaWAN
  #include <LoRaWAN.h>
  #include <EEPROM.h> // For Storing  Frame Counter
  #define DIO0 PIN_B0
  #define NSS  PIN_B1
  RFM95 rfm(DIO0,NSS);
  LoRaWAN lora = LoRaWAN(rfm);
  uint16_t Frame_Counter_Tx = 0x0000;
#endif

#ifdef RF_RFM69
  // Include RFM69
  #include <RFM69_f.h>
  RFM69 radio;
#endif

// Create Sensor Class
#if defined HAS_BME280 || defined HAS_BME280_BRIGHTNESS || defined HAS_BME280_ALARM
  #include <BME280.h>
  BME280 sensor;
#endif

#if defined HAS_SHT21 || defined HAS_SHT21_BRIGHTNESS || defined HAS_SHT21_ALARM
  #include <SHT21.h>
  SHT21 sensor;
#endif

#if defined HAS_ALARM || defined HAS_SHT21_ALARM || defined HAS_BME280_ALARM
  volatile boolean alarm = false;

  // Get the Interrupt Mask for the selected Alarm PIN
  #if ALARM_PIN == PIN_A0
    #define ALARM_INT PCINT0
  #elif ALARM_PIN == PIN_A1
    #define ALARM_INT PCINT1
  #elif ALARM_PIN == PIN_A2
    #define ALARM_INT PCINT2
  #elif ALARM_PIN == PIN_A3
    #define ALARM_INT PCINT3
  #elif ALARM_PIN == PIN_A7
    #define ALARM_INT PCINT7
  #elif ALARM_PIN == PIN_B2
    #define ALARM_INT PCINT9
  #endif
#endif

#ifdef DS18B20_PIN
  #include <OneWire.h> 
  #include <DallasTemperature.h>
  OneWire oneWire(DS18B20_PIN);
  DallasTemperature sensors(&oneWire);
#endif

// Global Variable to Track Deep Sleep
uint16_t sleep_interval;

#ifdef LED_PIN
void blink(uint8_t num) {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 0);
  for (uint8_t i=0; i<num*2; i++) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    delay(100);
  }
  digitalWrite(LED_PIN, 0);
}
#endif


#if defined HAS_SHT21_BRIGHTNESS || defined HAS_BME280_BRIGHTNESS

int16_t brightness()
{
  unsigned int counter;
  // LED Anode auf OUTPUT/LOW
  pinMode(LED_A, OUTPUT);
  digitalWrite(LED_A, LOW);

  // LED Kathode auf OUTPUT/HIGH
  pinMode(LED_K, OUTPUT);
  digitalWrite(LED_K, HIGH);
  delayMicroseconds(4);

  // Kathode wieder auf INPUT
  pinMode(LED_K,INPUT);
  digitalWrite(LED_K, LOW);
  // In einer Schleife zählen, bis Kathode auf LOW geht
  for ( counter = 0; counter < 65000; counter++) {
    if (digitalRead(LED_K)==0) break;
     delayMicroseconds(5);
  }
  return counter;
}
#endif

// Setup Wakeup Interrupt Timer
void init_wdt()
{
  MCUSR &= ~(1<<WDRF);
  // Start timed sequence
  // Set Watchdog Change Enable bit
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // Set new prescaler (8 sec), unset reset enable
  // enable WDT interrupt
  WDTCSR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0);
}

// Enter Sleepmode, Sleep for s Seconds
void sleep(uint16_t s)
{
  s = s/8;
  sleep_interval = 0;
  while (sleep_interval < s) {
  // in case of alarm, break loop and transmit immediatly
  #if defined HAS_ALARM || defined HAS_SHT21_ALARM || defined HAS_BME280_ALARM
    if( alarm == true){
      return;
    }
  #endif
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
  }
}

// Watchdog Callback for Sleep Timer
ISR(WATCHDOG_vect) {
  sleep_interval++;  // set global flag
  // Start timed sequence
  // Set Watchdog Change Enable bit
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // Set new prescaler (8 sec), unset reset enable
  // enable WDT interrupt
  WDTCSR = (1<<WDIE)|(1<<WDP3)|(1<<WDP0);
}

#if defined HAS_ALARM || defined HAS_SHT21_ALARM || defined HAS_BME280_ALARM
// innterrupt handler pin change
ISR(PCINT0_vect)
{
    sleep_disable();
    #ifdef HAS_LED
      blink(1);
    #endif
    alarm = true;
}

#endif
// Get Battery Voltage
int32_t readVcc() {
  bitClear(PRR, PRADC);
  ADCSRA |= bit(ADEN); // Enable the ADC
  int32_t result;
  ADMUX = _BV(MUX5) | _BV(MUX0); // For ATtiny84
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate Vcc in mV
  ADCSRA &= ~ bit(ADEN);
  bitSet(PRR, PRADC); // Disable the ADC to save power
  return result;
}

// Crude  Wear Leveling Algorithm to Spread the EEPROM Cell Wear Over
// the first 64 Byte. Using this Method the Theoretical EEPROM Livetime
// should be around 60 Years at a 10 Minute Sending Interval
// (100000 Erase Cycles per Cell * 32 Locations / 144 Measurements a day * 365)
//
// Returns the Next EEPROM Address for Saving the Frame Counter
uint8_t calcEepromAddr(uint16_t framecounter) {
    uint8_t eeprom_addr = ((framecounter%32)*sizeof(framecounter));
    if (eeprom_addr == 0) {
      eeprom_addr = 62;
    } else {
      eeprom_addr = eeprom_addr-sizeof(framecounter);
    }
    return eeprom_addr;
}

void setup()
{
  // Initialize Sleep Timer
  init_wdt();
  PRR = bit(PRTIM1);

  #ifdef RF_LORA
    // Setup LoraWAN
    rfm.init();
    lora.setKeys(NwkSkey, AppSkey, DevAddr);

    // Get Framecounter from EEPROM
    // Check if EEPROM is initialized
    if (EEPROM.read(511) != 0x42) {
      // Set first 64 byte to 0x00 for the wear leveling hack to work
      for (int i = 0; i < 64; i++)
        EEPROM.write(i, 0x00);
      // Write the magic value so we know it's initialized
      EEPROM.write(511, 0x42);
    } else {
      // Get the Last Saved (=Highest) Frame Counter
      uint16_t Frame_Counter_Sv = 0x00000000;
      uint8_t eeprom_addr = 0x0000;
      EEPROM.get(eeprom_addr, Frame_Counter_Sv);
      while (eeprom_addr < 32*sizeof(Frame_Counter_Tx)) {
        if (Frame_Counter_Sv > Frame_Counter_Tx) {
          Frame_Counter_Tx = Frame_Counter_Sv;
        } else {
            break;
        }
        eeprom_addr += sizeof(Frame_Counter_Tx);
        EEPROM.get(eeprom_addr, Frame_Counter_Sv);
      }
    }
  #endif

  #ifdef RF_RFM69
    // Setup RFM69 Module
    radio.initialize(RF69_433MHZ,RFM69_NODEID,RFM69_NETWORKID);
    #ifdef RFM69_ENCKEY
      radio.encrypt(RFM69_ENCKEY);
    #endif
    radio.setPowerLevel(RFM69_TXPOWER);
    radio.sleep();
  #endif

  #if defined HAS_ALARM || defined HAS_SHT21_ALARM || defined HAS_BME280_ALARM
    MCUCR  = (MCUCR & ~(bit(ISC01)|bit(ISC00))) | bit(ISC01);  // fallende Flanke 
    GIMSK = (1<<PCIE0);
    PCMSK0 = (1<<ALARM_INT);
    pinMode(ALARM_PIN, INPUT_PULLUP);
  #endif

  #ifdef DS18B20_POWER
    pinMode(DS18B20_POWER, OUTPUT); // set power pin for DS18B20 to output
  #endif
  
  // Setup LED if defined
  #ifdef LED_PIN
    pinMode(LED_PIN, OUTPUT);
    blink(1);
  #endif
}

void loop()
{
  // Create Data Structure for Sensor Data
  #ifdef HAS_NO_SENSOR
    struct lora_data {
      uint8_t bat;
    } __attribute__ ((packed)) data; 
  #elif defined HAS_ALARM
      struct lora_data {
      uint8_t bat;
      uint8_t alarm;
    } __attribute__ ((packed)) data; 
  #elif defined HAS_SHT21
    struct lora_data {
      uint8_t bat;
      int32_t temperature;
      int32_t humidity;
    } __attribute__ ((packed)) data;
  #elif defined HAS_SHT21_BRIGHTNESS
    struct lora_data {
      uint8_t bat;
      int32_t temperature;
      int32_t humidity;
      int16_t brightness;
    } __attribute__ ((packed)) data;
  #elif defined HAS_BME280
    struct lora_data {
      uint8_t bat;
      int32_t temperature;
      int32_t humidity;
      int32_t pressure;
    } __attribute__ ((packed)) data;
  #elif  defined HAS_BME280_BRIGHTNESS
    struct lora_data {
      uint8_t bat;
      int32_t temperature;
      int32_t humidity;
      int32_t pressure;
      int16_t brightness;
    } __attribute__ ((packed)) data;
  #elif defined HAS_SHT21_ALARM
    struct lora_data {
      uint8_t bat;
      int32_t temperature;
      int32_t humidity;
      uint8_t alarm;
    } __attribute__ ((packed)) data;       
  #elif defined HAS_BME280_ALARM
      struct lora_data {
      uint8_t bat;
      int32_t temperature;
      int32_t humidity;
      int32_t pressure;
      uint8_t alarm;
    } __attribute__ ((packed)) data;
  #elif defined DS18B20_PIN
   struct lora_data {
      uint8_t bat;
      uint8_t count; //sensor count
      int temp1;
      int temp2;     //fixme dynamic values via count
    } __attribute__ ((packed)) data; 
  #endif

  // Get Sensor Data
  #if defined HAS_BME280 || defined HAS_BME280_BRIGHTNESS || defined HAS_BME280_ALARM
    sensor.getData(&data.temperature, &data.pressure, &data.humidity);
  #endif

  #if defined HAS_SHT21 || defined HAS_SHT21_BRIGHTNESS || defined HAS_SHT21_ALARM
    data.temperature = (int32_t)(sensor.getTemperature()*100);
    data.humidity    = (int32_t)(sensor.getHumidity()*100);
  #endif
  
  #if defined HAS_SHT21_BRIGHTNESS || defined HAS_BME280_BRIGHTNESS
    data.brightness = (int16_t)(brightness());
  #endif

  #if defined HAS_ALARM || defined HAS_SHT21_ALARM || defined HAS_BME280_ALARM
    data.alarm = alarm;
    alarm = false;
  #endif

  #if defined DS18B20_PIN

    #ifdef DS18B20_POWER
      digitalWrite(DS18B20_POWER, HIGH); // turn DS18B20 sensor on
    #endif
    delay(100);     // Allow 5ms for the sensor to be ready
    sensors.begin(); //start up temp sensor
    delay(100); 
    data.count = sensors.getDeviceCount();
    sensors.requestTemperatures(); // Get the temperature
    data.temp1=(sensors.getTempCByIndex(0)*100); // Read first sensor and convert to integer
    //Fixme , add more dynamic code 
    data.temp2=(sensors.getTempCByIndex(1)*100); // Read second sensor and convert to integer
    #ifdef DS18B20_POWER
      digitalWrite(DS18B20_POWER, LOW); // turn DS18B20 off
    #endif
  #endif

  // Add Battery Voltage, 20mv steps, encoded into 1 Byte
  uint32_t batv = readVcc();
  data.bat = (uint8_t)(batv/20);
  if (batv % 20 > 9)
    data.bat += 1;

  // LED On before Sending
  #ifdef LED_ON_SEND
    digitalWrite(LED_PIN, 1);
  #endif
  
  #ifdef RF_LORA
    #ifdef HAS_NO_SENSOR
    // Send Packet in all 6 SFs for Beacon Mode
    unsigned char Frame_Port =0x07;
    for  (int i = SF7BW125; i<=SF12BW125; i++) {
      lora_data tdata = data;
      // Some FrameCounter Trickery to not write the value to EEPROM 6 Times but still have a working WearLeveling
      lora.Send_Data((unsigned char *)&tdata, sizeof(tdata), i+(Frame_Counter_Tx*6), static_cast<lora_dr>(i), Frame_Port);
      Frame_Port++;
      delay(25);
    }
    #else
    // Send LoRa Packet, Increment Frame Counter
    lora.Send_Data((unsigned char *)&data, sizeof(data), Frame_Counter_Tx, SF7BW125, 0x01);
    #endif
    // Save the next FrameCounter to EEPROM
    Frame_Counter_Tx++;
    EEPROM.put(calcEepromAddr(Frame_Counter_Tx), Frame_Counter_Tx);
  #endif

  #ifdef RF_RFM69
    radio.send(RFM69_GATEWAY, &data, sizeof(data));
    radio.sleep();
  #endif

  // Led Off after Sending
  #ifdef LED_ON_SEND
    digitalWrite(LED_PIN, 0);
  #endif

  // Sleep until next Measurement
  sleep(SLEEP_TIME);
}
