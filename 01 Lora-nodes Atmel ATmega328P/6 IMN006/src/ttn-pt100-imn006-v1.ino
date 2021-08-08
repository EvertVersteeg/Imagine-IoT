/*    IMN006
Program for Imagine-Node with:
  - OTAA(connect to TTN)
  - CayenneLPP Low Power Payload
  - PT100 // MAX31865

Imagine Solutions BV 
rev. 6-11-2019
http://www.imagineiot.nl
http://www.imaginedata.nl

Evert Versteeg
*/

// ------------------------------
// Init
// ------------------------------
#include <LMiC_IMN.h>                                         // Imagine LMiC library


#define LED_PIN        21                                     // Digitale uitgang waarop een led is aangesloten
#include <Adafruit_MAX31865.h>
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

// Variabelen
float temperature = 0;
float weerstand = 0;

// Declaring variables
static const u1_t PROGMEM APPEUI[8]={ xxxxx };                                    // This EUI must be in little-endian format.
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
static const u1_t PROGMEM DEVEUI[8]={ xxxxx };                                    // This should also be in little endian format.
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
static const u1_t PROGMEM APPKEY[16] = { xxxxxx };                                // This key should be in big endian format.
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}
static osjob_t sendjob;                                                           // Instantie aanmaken van sendjob

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(5, 6, 7, 8);

// ------------------------------
// Setup
// ------------------------------
void setup() {
    Serial.begin(9600);
    delay(100);
    while(!Serial);                                                         // time to get serial running
    delay(100);
    unsigned status;
    // default settings
    pinMode(LED_PIN, OUTPUT);
    thermo.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
    imn_lmic_setup();                                                       // Init LoRa LMiC
}

// ------------------------------
// Main loop
// ------------------------------
void loop() {
  Payload.reset();                                                          // Read sensors
  uint16_t rtd = thermo.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio,8);
  
  weerstand = RREF*ratio;
  Serial.print("Resistance = "); Serial.println(weerstand);
  
  temperature = thermo.temperature(RNOMINAL, RREF);
  Serial.print("Temperature = "); Serial.println(temperature);

  // Check and print any faults
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    thermo.clearFault();
  }
  Serial.println();
  delay(1000);
  os_runloop_once();                                                        // Stuur bericht
  Payload.addTemperature(1,temperature);
  Payload.addAnalogInput(2,weerstand);
  Payload.addAnalogInput(3,ratio);                    
  LMIC_setTxData2(1, Payload.getBuffer(), Payload.getSize(), 0);            // Prepare upstream data transmission at the next possible time.
  Serial.println(F("Packet queued"));
  imn_lmic_wait_for_txcomplete();                                           // Sleep
  delay(300000);
}
