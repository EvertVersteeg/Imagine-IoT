/*
Program for Imagine-Node with:
  - OTAA(connect to TTN)
  - Cayenne
  - SPS30 fijnstof sensor
 
 Version V1

Imagine Solutions BV 
rev. 04-09-2020

*/

// ------------------------------
// Init
// ------------------------------
#include <LMiC_IMN.h>                                         // Imagine LMiC library
#include "sps30.h"

// Declaring variables
static const u1_t PROGMEM APPEUI[8]={ 0xXX }; // This EUI must be in little-endian format.
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
static const u1_t PROGMEM DEVEUI[8]={ 0xXX }; // This should also be in little endian format.
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
static const u1_t PROGMEM APPKEY[16] = { 0xXX }; // This key should be in big endian format.
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}
static osjob_t sendjob;
const unsigned TX_INTERVAL = 300;
float temperature = 20;

#define SP30_COMMS I2C_COMMS
#define TX_PIN 19
#define RX_PIN 18

SPS30 sps30;
// ------------------------------
// Setup
// ------------------------------
void setup() {
    Serial.begin(9600);
    delay(100);
    Serial.println(F("Start Setup"));
    imn_lmic_setup();                                                      // Init LoRa LMiC
    Serial.println(F("Trying to connect SPS30"));
    sps30.EnableDebugging(DEBUG);
    Serial.println(F("DEBUG"));
    if (TX_PIN != 0 && RX_PIN != 0) sps30.SetSerialPin(RX_PIN,TX_PIN);
    if (! sps30.begin(SP30_COMMS)){
      Serial.println(F("Could not initialize communication channel."));
    }
    if (sps30.start()) {
      
    }
    else {
      Serial.println(F("Could NOT start measurement"));
    }
    Serial.println(F("Setup complete"));
    if (SP30_COMMS == I2C_COMMS) {
      if (sps30.I2C_expect() == 4)
        Serial.println(F(" !!! Due to I2C buffersize only the SPS30 MASS concentration is available !!! \n"));
    }

}

// ------------------------------
// Main loop
// ------------------------------
void loop() {
    uint8_t ret, error_cnt = 0;
    struct sps_values val;
    Payload.reset();                                                          // Read sensors
    ret = sps30.GetValues(&val);
    float PM1 = val.MassPM1;
    float PM2 = val.MassPM2;
    float PM4 = val.MassPM4;
    float PM10= val.MassPM10;
    os_runloop_once();                                                        // Stuur bericht
    Payload.addAnalogOutput(1,PM1);
    Payload.addAnalogOutput(2,PM2);  
    Payload.addAnalogOutput(3,PM4);  
    Payload.addAnalogOutput(4,PM10);                 
    LMIC_setTxData2(1, Payload.getBuffer(), Payload.getSize(), 0);            // Prepare upstream data transmission at the next possible time.
    Serial.println(F("Packet queued"));
    imn_lmic_wait_for_txcomplete();                                           // Sleep
    delay(600000);
        
}
