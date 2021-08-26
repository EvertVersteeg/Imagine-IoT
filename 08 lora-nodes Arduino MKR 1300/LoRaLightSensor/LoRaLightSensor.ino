/*
  LOraLightSensor v1.0
  ImagineSolutions BV
*/
#include <MKRWAN.h>
#include <CayenneLPP.h>
#include <ArduinoLowPower.h>
#include <BH1750.h>
#include <Wire.h>
#include "arduino_secrets.h"
#include "config.h"
CayenneLPP lpp(size);
LoRaModem modem;
BH1750 lightMeter(0x23);


//*****************************************************************************
// SETUP
//*****************************************************************************
void setup() {
  Serial.begin(115200);
  //while (!Serial);
  
  Wire.begin();
  delay(1000);
  
  // begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
  } else {
    Serial.println(F("Error initialising BH1750"));
  }
  
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
  LowPower.sleep(300000);
}

//*****************************************************************************
// Function: Read all sensor values
//*****************************************************************************
void readSensorValues(){
  if (lightMeter.measurementReady()) {
    illuminance = lightMeter.readLightLevel();
    delay(150);
   }
   if (!lightMeter.measurementReady()) {
    Serial.println("Sensor not ready");
   }
}


//*****************************************************************************
// Function: Print sensor values to serial interface
//*****************************************************************************
void printValuesToSerial(){
  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lux");
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
