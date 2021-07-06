#include "Microchip24AA02E.h"

mac64 mac;

void setup() {
  Serial.begin(9600);  // start serial for output
  while(!Serial) {}
  Serial.println("begin.");
}

void loop() {
  MacReader.readMac64(mac);
  for (int i = 0; i < sizeof(mac) / sizeof(mac[0]); i++) {
    Serial.print(mac[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
