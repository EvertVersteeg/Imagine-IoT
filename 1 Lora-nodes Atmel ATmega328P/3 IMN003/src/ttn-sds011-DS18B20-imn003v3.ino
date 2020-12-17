/*
Test program to test the node with OTAA (connect to TTN). Version V2


Imagine Solutions BV 
rev. 7-9-2019

v1 basic OTAA
v2 added Cayenne
v3 added DS18B20 and SDS011 power management
*/

#include <LMiC_IMN.h>                                         // Imagine LMiC library
//#include <SPI.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <SDS011.h>


#define SDSrxPin       A0
#define SDStxPin       A1

const int TempBuitenPin = 8;
SDS011 my_sds;
float p101;
float p102;
float p103;
float p104;
float p105;
float p251;
float p252;
float p253;
float p254;
float p255;
float temperature1;
float temperature2;
float temperature3;
float temperature4;
float temperature5;

int error;
static const u1_t PROGMEM APPEUI[8]={ xxxxx }; // This EUI must be in little-endian format.
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
static const u1_t PROGMEM DEVEUI[8]={ xxxxxx }; // This should also be in little endian format.
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
static const u1_t PROGMEM APPKEY[16] = { xxxxxx }; // This key should be in big endian format.
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

static osjob_t sendjob;

// Setup 1 wire
OneWire TempBuiten(TempBuitenPin);
DallasTemperature TempBuitenSensor(&TempBuiten);

// ------------------------------
// Setup
// ------------------------------
void setup() {
    Serial.begin(9600);
    delay(100);
    while(!Serial);                                                         // time to get serial running
    delay(100);
    unsigned status;
    my_sds.begin(SDSrxPin,SDStxPin);
    pinMode(LED_PIN, OUTPUT);
    TempBuitenSensor.begin();
    Serial.println(F("Start"));
    imn_lmic_setup();                                                       // Init LoRa LMiC
}

// ------------------------------
// Main loop
// ------------------------------
void loop() {
  Payload.reset();
  int error;
  my_sds.newwakeup();
  delay(30000); // Wacht 3 seconden (laten draaien fan)
  digitalWrite(LED_PIN, HIGH);
  
  // eerste meting
  TempBuitenSensor.requestTemperatures();
  temperature1 = TempBuitenSensor.getTempCByIndex(0);
  error = my_sds.read(&p251,&p101);
  
  // tweede meting
  delay(10000); // Wacht 3 seconden (laten draaien fan)
  TempBuitenSensor.requestTemperatures();
  temperature2 = TempBuitenSensor.getTempCByIndex(0);
  error = my_sds.read(&p252,&p102);

  // derde meting
  delay(10000); // Wacht 3 seconden (laten draaien fan)
  TempBuitenSensor.requestTemperatures();
  temperature3 = TempBuitenSensor.getTempCByIndex(0);
  error = my_sds.read(&p253,&p103);

  // vierde meting
  delay(10000); // Wacht 3 seconden (laten draaien fan)
  TempBuitenSensor.requestTemperatures();
  temperature4 = TempBuitenSensor.getTempCByIndex(0);
  error = my_sds.read(&p254,&p104);
  
  Serial.println("Temperature 1 =" + String(temperature1)+ " C");
  Serial.println("Temperature 2 =" + String(temperature2)+ " C");
  Serial.println("Temperature 3 =" + String(temperature3)+ " C");
  Serial.println("Temperature 4 =" + String(temperature4)+ " C");

  if (! error) {
        Serial.println("P2.5-1: "+String(p251));
        Serial.println("P10-1:  "+String(p101));
        Serial.println("P2.5-2: "+String(p252));
        Serial.println("P10-2:  "+String(p102));
        Serial.println("P2.5-3: "+String(p253));
        Serial.println("P10-3:  "+String(p103));
        Serial.println("P2.5-4: "+String(p254));
        Serial.println("P10-4:  "+String(p104));
        }
      
   my_sds.sleep();
   digitalWrite(LED_PIN, LOW);   


  os_runloop_once();                                                        // Stuur bericht
  Payload.addTemperature(1,temperature1);
  Payload.addTemperature(2,temperature2);
  Payload.addTemperature(3,temperature3);
  Payload.addTemperature(4,temperature4);
  Payload.addAnalogInput(10, p251);
  Payload.addAnalogInput(11, p252);
  Payload.addAnalogInput(12, p253);
  Payload.addAnalogInput(13, p254);
  Payload.addAnalogInput(20, p101);
  Payload.addAnalogInput(21, p102);
  Payload.addAnalogInput(22, p103);
  Payload.addAnalogInput(23, p104);

                    
  LMIC_setTxData2(1, Payload.getBuffer(), Payload.getSize(), 0);            // Prepare upstream data transmission at the next possible time.
  Serial.println(F("Packet queued"));
  imn_lmic_wait_for_txcomplete();                                           // Sleep
  delay(240000);
}
