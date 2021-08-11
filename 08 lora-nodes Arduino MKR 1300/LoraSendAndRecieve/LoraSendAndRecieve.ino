/*

  Lora Send And Receive

  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.

  This example code is in the public domain.

*/
#include <MKRWAN.h>
LoRaModem modem;
// Uncomment if using the Murata chip as a module
// LoRaModem modem(Serial1);
#include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
String appEui = SECRET_APP_EUI;
String appKey = SECRET_APP_KEY;
int payLoadDown = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial);
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

  // Set poll interval to 60 secs.

  modem.minPollInterval(60);

  // NOTE: independently by this setting the modem will
  // not allow to send more than one message every 2 minutes,
  // this is enforced by firmware and can not be changed.
}

void loop() {
  delay(60000);
  float temperature = 20.1;
  String msg = String(temperature);

  Serial.println();
  Serial.print("Sending: " + msg + " - ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
    Serial.print(" ");
  }

  Serial.println();
  int err;
  modem.beginPacket();
  modem.print(msg);
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
    Serial.println("(you may send a limited amount of messages per minute, depending on the signal strength");
    Serial.println("it may vary from 1 message every couple of seconds to 1 message every minute)");
  }

  delay(1000);
  if (!modem.available()) {
    Serial.println("No downlink message received at this time.");
    return;
  }

  char rcv[64];
  int i = 0;
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
  }
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(rcv[j] >> 4, HEX);
    Serial.print(rcv[j] & 0xF, HEX);
    //Serial.print(j);
    Serial.print(" ");
  }
  //Serial.println(rcv[0] >> 4);
  payLoadDown=((rcv[0] >> 4));
  //Serial.println(payLoadDown);
  if (payLoadDown == 1){
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Led LOW");            // Downlink 0x10
    Serial.println();
      }
  if (payLoadDown == 2){
    digitalWrite(LED_BUILTIN, HIGH);      // Downlink 0x20
    Serial.println("Led HIGH");
    Serial.println();
    }
  if (payLoadDown == 3){
    Serial.println("Restart");              // Downlink 0x30
    Serial.println();
    delay(5000);
    modem.restart();
  }
  

}
