
#include "Microchip24AA02E.h"

mac48 mac;

void setup() {
  Serial.begin(9600);  // start serial for output
  while(!Serial) {}
  Serial.println("begin.");
}

void loop() {
  Serial.print("EUI48: ");
  MacReader.readMac48(mac);
  for (int i = 0; i < sizeof(mac) / sizeof(mac[0]); i++) {
    if (mac[i]<16){
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    Serial.print(" ");
  }

  Serial.println();
  delay(1000);
}
