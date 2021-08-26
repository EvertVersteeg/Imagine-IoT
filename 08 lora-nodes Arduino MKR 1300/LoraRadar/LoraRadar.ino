/*
  Based on the Arduino example:Lora Send And Receive
  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.
  
*/
//#include <MKRWAN.h>
#include "MKRWAN.h"
#include <CayenneLPP.h>
#include "arduino_secrets.h"
#include "config.h"
CayenneLPP lpp(size);
LoRaModem modem;

int val =0;

// Please enter your sensitive data in the Secret tab or arduino_secrets.h
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;


//*****************************************************************************
// SETUP
//*****************************************************************************
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(1, INPUT);
  Serial.begin(115200);
  //while (!Serial);
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your module version is: ");
  Serial.println(modem.version());
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());
  int connected = modem.joinOTAA(appEui, appKey);
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  modem.setADR(false);
  modem.dataRate(5); //Method dataRate uses argument dr from 0 (SF12/BW125) to 5 (SF7BW125)
  // Set poll interval to 30 secs.
  modem.minPollInterval(30);
  sendZero();
}

//*****************************************************************************
// MAIN LOOP
//*****************************************************************************
void loop() {
  delay(100);
  val = digitalRead(1);
  //Serial.println(val);
  if (val == 1){
    send();
  }
}

void send(){
  lpp.reset();
  lpp.addDigitalInput(1, val);
  Serial.println("Sending");
  int err;
  modem.dataRate(5);
  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());
  Serial.println("Send 1");
  err = modem.endPacket(false);
  
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  // Getting the settings
  Serial.println("Sleep");
  delay(120000);
  Serial.println("Awake");
  lpp.reset();
  val=0;
  lpp.addDigitalInput(1, val);

  Serial.println("Sending");
  modem.dataRate(5);
  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());
  Serial.println("Send 0");
  err = modem.endPacket(false);
  
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  // Getting the settings
  Serial.println("Sleep");
  delay(120000);
  Serial.println("Awake");

  
}
void sendZero(){
  val=0;
  
  lpp.reset();
  lpp.addDigitalInput(1, val);

  Serial.println("Sending");
  int err;
  modem.dataRate(5);
  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());
  Serial.println("Send reset 0");
  err = modem.endPacket(false);
  
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }
  // Getting the settings
  Serial.println("Sleep");
  delay(120000);
  Serial.println("Awake");
}
