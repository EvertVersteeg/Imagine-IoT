/*    IMN005
Program for Imagine-Node with:
  - OTAA(connect to TTN)
  - CayenneLPP Low Power Payload
  - HX711 Load Cell sensoren
  - 2x DS18B20 BeeHive sensor


  
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
#include <Wire.h>                                             // I2C library tbv BME280 sensor => https://www.arduino.cc/en/reference/wire
#include <OneWire.h> 
#include <DallasTemperature.h>
#include "HX711.h"
#define LED_PIN        21                                     // Digitale uitgang waarop een led is aangesloten
//#define ONE_WIRE_BUS 6 // beehive
//#define ONE_WIRE_BUS_2 5 // buiten
const int TempBuitenPin = 6;
const int TempBinnenPin = 5;

// Variabelen
float calibration_factor = 22200;                             // this calibration factor is adjusted according to my load cell
float units;                                                  // Variabele voor gewicth Load Cell
float temperature;
float temperature_bee;

// Lora parameters en functies
static const u1_t PROGMEM APPEUI[8]={ xxxxx };                                                     // This EUI must be in little-endian format.
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}                                                                                  // Functie voor aanmaken APP-eui
static const u1_t PROGMEM DEVEUI[8]={ xxxxx };                                                     // This should also be in little endian format.
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}                                                                                  // Functie voor aanmaken DEV-eui
static const u1_t PROGMEM APPKEY[16] = { xxxxx };                                                 // This key should be in big endian format.
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}                                                                                // Functie voor aanmaen APP-key
static osjob_t sendjob;                                                                                                                     // Instantie aanmaken van sendjob

// Setup gewichtsensoren op pin 7 en 8 (via 1K weerstand) poort 7 => SCK, poort 8 => DT; Power: GND + 5V
HX711 scale(7, 8);



// Setup 1 wire
OneWire TempBuiten(TempBuitenPin);
OneWire TempBinnen(TempBinnenPin);
DallasTemperature TempBuitenSensor(&TempBuiten);
DallasTemperature TempBinnenSensor(&TempBinnen);

// ------------------------------
// Setup
// ------------------------------
void setup() {
    Serial.begin(9600);
    delay(100);
    while(!Serial);                                                         // time to get serial running
    delay(100);
    unsigned status;
    pinMode(LED_PIN, OUTPUT);
    TempBuitenSensor.begin();
    TempBinnenSensor.begin();
    scale.set_scale();
    //scale.tare();
    scale.set_scale(calibration_factor);                                    //Adjust to this calibration factor//Reset the scale to 0
    Serial.println(F("Start"));
    imn_lmic_setup();                                                       // Init LoRa LMiC

}

// ------------------------------
// Main loop
// ------------------------------
void loop() {
  Payload.reset();                                                          // Read sensors
  units = scale.get_units(), 10;
  delay(10000);
  TempBuitenSensor.requestTemperatures();
  delay(10000);
  temperature_bee = TempBuitenSensor.getTempCByIndex(0);
  delay(10000);
  TempBinnenSensor.requestTemperatures();
  delay(10000);
  temperature = TempBinnenSensor.getTempCByIndex(0);                     
  if (units < 0)
  {
    units = 0.00;
  }
  units = units - 37.53;
  //Serial.println("Vcc=" + String(Vcc)+ " V");
  //Serial.println("CpuTemp=" + String(CpuTemp)+ " C");
  Serial.println("Gewicht=" + String(units)+ " kg");
  //Serial.println("Pressure=" + String(pressure)+ " hPa");
  //Serial.println("Humidity=" + String(relative_humidity)+ " %");
  Serial.println("Temperature=" + String(temperature)+ " C");
  Serial.println("Temperature bee=" + String(temperature_bee)+ " C");
  //Serial.println("Altitude=" + String(altitude)+ " m");
  delay(10000);
  os_runloop_once();                                                        // Stuur bericht
  Payload.addTemperature(1,temperature);
  Payload.addTemperature(2,temperature_bee);
  Payload.addAnalogInput(19, units);                      
  LMIC_setTxData2(1, Payload.getBuffer(), Payload.getSize(), 0);            // Prepare upstream data transmission at the next possible time.
  //Serial.println(F("Packet queued"));
  imn_lmic_wait_for_txcomplete();                                           // Sleep
  delay(190000);
}
