/*
  MKR ENV Shield - Read and Store Sensors
  This example reads the sensors on-board the MKR ENV shield
  and prints them to the Serial Monitor once a second.
  The circuit:
  - Arduino MKR board
  - Arduino MKR ENV Shield attached
  => th UV sensor is not mounted on a R2 board!! => removed the sensor
  => sensor values are stored on the SD card in a CSV file.
*/

#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>
#include <RTCZero.h>
// chip select for SD card
const int SD_CS_PIN = 4;  
float temperature = 0;
float humidity    = 0;
float pressure    = 0;
float illuminance = 0;
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16;
/* Change these values to set the current initial date */
const byte day = 10;
const byte month = 8;
const byte year = 21;
File dataFile;
RTCZero rtc;


void setup() {
  Serial.begin(9600);
  while (!Serial);
  rtc.begin(); // initialize RTC
  // Set the time
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  // Set the date
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
    // init SPI
  SPI.begin();
  delay(100);

  // init SD card
  if(!SD.begin(SD_CS_PIN)) {
    Serial.println("Failed to initialize SD card!");
    while (1);
  }

  // init the logfile
  dataFile = SD.open("log-0000.csv", FILE_WRITE);
  delay(1000);

  // init the CSV file with headers
  dataFile.println("temperature,humidity,pressure,illuminance");

  // close the file
  dataFile.close();
  delay(100);
}

void loop() {
  Serial.println("Open file");
  // init the logfile
  dataFile = SD.open("log-0000.csv", FILE_WRITE);
  delay(1000);
  
  // read all the sensor values
  temperature = ENV.readTemperature();
  humidity    = ENV.readHumidity();
  pressure    = ENV.readPressure();
  illuminance = ENV.readIlluminance();
  
  // print each of the sensor values
  dataFile.print(temperature);
  dataFile.print(",");
  dataFile.print(humidity);
  dataFile.print(",");
  dataFile.print(pressure);
  dataFile.print(",");
  dataFile.println(illuminance);

  // close the file
  dataFile.close();
  Serial.println("Close file");

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
  // Print date...

  Serial.print(rtc.getDay());

  Serial.print("/");

  Serial.print(rtc.getMonth());

  Serial.print("/");

  Serial.print(rtc.getYear());

  Serial.print(" ");

  // ...and time

  Serial.print(rtc.getHours());

  Serial.print(":");

  Serial.print(rtc.getMinutes());

  Serial.print(":");

  Serial.print(rtc.getSeconds());

  Serial.println();

  // wait 5 second to print again
  delay(5000);
}
