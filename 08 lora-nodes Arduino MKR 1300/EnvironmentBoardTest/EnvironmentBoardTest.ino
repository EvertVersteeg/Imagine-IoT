/*
  MKR ENV Shield - Read Sensors
  This example reads the sensors on-board the MKR ENV shield
  and prints them to the Serial Monitor once a second.
  The circuit:
  - Arduino MKR board
  - Arduino MKR ENV Shield attached
  => th UV sensor is not mounted on a R2 board!! => removed the sensor
*/

#include <Arduino_MKRENV.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
}

void loop() {
  // read all the sensor values
  float temperature = ENV.readTemperature();
  float humidity    = ENV.readHumidity();
  float pressure    = ENV.readPressure();
  float illuminance = ENV.readIlluminance();

  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Pressure    = ");
  Serial.print(pressure);
  Serial.println(" kPa");
  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lx");
  // print an empty line
  Serial.println();

  // wait 5 second to print again
  delay(5000);
}
