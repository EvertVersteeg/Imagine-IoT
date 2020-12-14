/*
Program for Imagine-Node with:
  - OTAA(connect to TTN)
  - Cayenne
  - BMP280 sensor (Bosch) via I2C temperature, pressure and humidity
  - Sound sensor
  - Light sensor
  - Imagine Lmic


 
 Version V4


Imagine Solutions BV 
rev. 15-1-2020

*/

// ------------------------------
// Init
// ------------------------------
#include <LMiC_IMN.h>                                                                                                                       // Imagine LMiC library
#include <Wire.h>
#include <Adafruit_BMP280.h>




// Lora parameters en functies
static const u1_t PROGMEM APPEUI[8]={ 0xXX, 0xxx, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };                                                     // This EUI must be in little-endian format.
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}                                                                                  // Functie voor aanmaken APP-eui
static const u1_t PROGMEM DEVEUI[8]={ 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };                                                     // This should also be in little endian format.
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}                                                                                  // Functie voor aanmaken DEV-eui
static const u1_t PROGMEM APPKEY[16] = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };   // This key should be in big endian format.
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}                                                                                // Functie voor aanmaen APP-key
static osjob_t sendjob;                                                                                                                     // Instantie aanmaken van sendjob
//const unsigned TX_INTERVAL = 300;
const unsigned TX_INTERVAL = 60;
float sensorLicht = A1;
float sensorGeluid = A2;
float volts = 0;
float lichtniveau1 = 0;
float geluidsniveau1 = 0;
float lichtniveau2 = 0;
float geluidsniveau2 = 0;
float lichtniveau3 = 0;
float geluidsniveau3 = 0;
float lichtniveau4 = 0;
float geluidsniveau4 = 0;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

// init temperature sensor
Adafruit_BMP280 bmp; // I2C

// ------------------------------
// Setup
// ------------------------------
void setup() {
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BMP280 test"));
    if (!bmp.begin()) {
     Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
     while (1);
    }
    Serial.println(F("Starting"));
    imn_lmic_setup();
}

// ------------------------------
// Main loop
// ------------------------------
void loop() {
    Payload.reset();
    float pressure = (bmp.readPressure() / 100.0F);
    float temperature = bmp.readTemperature();
    float altitude = bmp.readAltitude(1013.25);
    Serial.println("Pressure=" + String(pressure)+ " hPa");
    Serial.println("Temperature=" + String(temperature)+ " C");
    Serial.println("Altitude=" + String(altitude)+ " m");
        
    // Meting 1
    lichtniveau1 = analogRead(sensorLicht);
    geluid();
    geluidsniveau1= volts;
    Serial.println("Licht 1=" + String(lichtniveau1));
    Serial.println("Geluid 1=" + String(geluidsniveau1));
    delay(25000);
        
    //Meting 2
    lichtniveau2 = analogRead(sensorLicht);
    geluid();
    geluidsniveau2=volts;
    Serial.println("Licht 2=" + String(lichtniveau2));
    Serial.println("Geluid 2=" + String(geluidsniveau2));
    delay(25000);
        
    //Meting 3
    lichtniveau3 = analogRead(sensorLicht);
    geluid();
    geluidsniveau3=volts;
    Serial.println("Licht 3=" + String(lichtniveau3));
    Serial.println("Geluid 3=" + String(geluidsniveau3));
    delay(25000);
        
    //Meting 4
    lichtniveau4 = analogRead(sensorLicht);
    geluid();
    geluidsniveau4=volts;
    Serial.println("Licht 4=" + String(lichtniveau4));
    Serial.println("Geluid 4=" + String(geluidsniveau4));
    delay(25000);

    //Middelen
    lichtniveau1 = (lichtniveau1 + lichtniveau2 + lichtniveau3 +lichtniveau4)/4;
    geluidsniveau1 = (geluidsniveau1 + geluidsniveau2 + geluidsniveau3 + geluidsniveau4)/4;
    os_runloop_once();
    Payload.addTemperature(1,temperature);
    Payload.addBarometricPressure(4,pressure);
    Payload.addAnalogInput(5,altitude);
        
    Payload.addAnalogInput(6,lichtniveau1);
    Payload.addAnalogInput(7,geluidsniveau1);

     Payload.addAnalogInput(8,lichtniveau2);
     Payload.addAnalogInput(9,geluidsniveau2); 

     Payload.addAnalogInput(10,lichtniveau3);
     Payload.addAnalogInput(11,geluidsniveau3); 

     Payload.addAnalogInput(12,lichtniveau4);
     Payload.addAnalogInput(13,geluidsniveau4); 
        
        // Prepare upstream data transmission at the next possible time.
    LMIC_setTxData2(1, Payload.getBuffer(), Payload.getSize(), 0);
    Serial.println(F("Packet queued"));
    imn_lmic_wait_for_txcomplete(); 
    delay(190000);
}

// Geluidsfunctie

void geluid() {
  unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
   
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorGeluid);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   //volts = (peakToPeak * 5.0) / 1024;  // convert to volts
   volts = peakToPeak;
   if (volts <0) {
    volts = 0;
   }
   if (volts > 327) {
    volts = 327;
   }
   return volts;
}
