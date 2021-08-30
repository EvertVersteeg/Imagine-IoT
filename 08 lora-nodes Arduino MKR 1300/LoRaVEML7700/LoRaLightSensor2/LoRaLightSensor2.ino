/*
  LOraLightSensor v1.0
  ImagineSolutions BV
*/
#include <MKRWAN.h>
#include <CayenneLPP.h>
#include <ArduinoLowPower.h>
#include "Adafruit_VEML7700.h"
#include <Wire.h>
#include "arduino_secrets.h"
#include "config.h"
CayenneLPP lpp(size);
LoRaModem modem;
Adafruit_VEML7700 veml = Adafruit_VEML7700();

//*****************************************************************************
// SETUP
//*****************************************************************************
void setup() {
  Serial.begin(115200);
  //while (!Serial);
  
  Wire.begin();
  delay(1000);
  
  // begin returns a boolean that can be used to detect setup problems.
  if (!veml.begin()) {
    Serial.println("Sensor not found");
    while (1);
  }
  Serial.println("Sensor found");

  veml.setGain(VEML7700_GAIN_1);
  veml.setIntegrationTime(VEML7700_IT_800MS);

  Serial.print(F("Gain: "));
  switch (veml.getGain()) {
    case VEML7700_GAIN_1: Serial.println("1"); break;
    case VEML7700_GAIN_2: Serial.println("2"); break;
    case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
    case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
  }

  Serial.print(F("Integration Time (ms): "));
  switch (veml.getIntegrationTime()) {
    case VEML7700_IT_25MS: Serial.println("25"); break;
    case VEML7700_IT_50MS: Serial.println("50"); break;
    case VEML7700_IT_100MS: Serial.println("100"); break;
    case VEML7700_IT_200MS: Serial.println("200"); break;
    case VEML7700_IT_400MS: Serial.println("400"); break;
    case VEML7700_IT_800MS: Serial.println("800"); break;
  }

  //veml.powerSaveEnable(true);
  //veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);

  veml.setLowThreshold(10000);
  veml.setHighThreshold(20000);
  veml.interruptEnable(true);
  
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  connectToLoRaWAN();
}

//*****************************************************************************
//LOOP
//*****************************************************************************
void loop() {
  readSensorValues();
  printValuesToSerial();
  sendSensorValues();
  
  // Debug
  int adr = modem.getADR();
  Serial.print("Your device Adaptive Data Rate setting is (0: off, 1: on): ");
  Serial.println(adr);
  String deviceadres = modem.getDevAddr();
  Serial.print("Your device adres is: ");
  Serial.println(deviceadres);
  
  // GO TO SLEEP
  LowPower.sleep(120000);
}

//*****************************************************************************
// Function: Read all sensor values
//*****************************************************************************
void readSensorValues(){
  illuminance = veml.readLux();
  white = veml.readWhite();
  raw = veml.readALS();

}


//*****************************************************************************
// Function: Print sensor values to serial interface
//*****************************************************************************
void printValuesToSerial(){
  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lux");
  Serial.print("White = ");
  Serial.print(white);
  Serial.println(" lux");
  Serial.print("raw ALS = ");
  Serial.print(raw);
  Serial.println(" lux");
  uint16_t irq = veml.interruptStatus();
  if (irq & VEML7700_INTERRUPT_LOW) {
    Serial.println("** Low threshold"); 
  }
  if (irq & VEML7700_INTERRUPT_HIGH) {
    Serial.println("** High threshold"); 
  }
}

  
//*****************************************************************************
// Function: Connect to LoraWan
//*****************************************************************************
void connectToLoRaWAN(){
  Serial.println("Connecting...");
  int connected = modem.joinOTAA(APP_EUI, APP_KEY);

  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  modem.setADR(true);   //set adaptive datrate
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
  delay(5000);
}

//*****************************************************************************
// Function: Send Sensor values
//*****************************************************************************
void sendSensorValues(){
  lpp.reset();
  lpp.addLuminosity(1, illuminance);
  lpp.addLuminosity(2, white);
  lpp.addLuminosity(3, raw);
  Serial.println("Sending message...");
  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());
  int error = modem.endPacket(false);  // set confirmed messages to false
  if (error > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
  Serial.println();
}
