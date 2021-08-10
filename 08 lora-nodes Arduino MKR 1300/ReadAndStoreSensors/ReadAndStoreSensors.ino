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
const byte minutes = 10;
const byte hours = 16;
/* Change these values to set the current initial date */
const byte day = 10;
const byte month = 8;
const byte year = 21;
char filename[] = "000000.CSV";
byte actualDay =0;
byte currentDay =0;
File dataFile;
RTCZero rtc;


void setup() {
  // init serial
  Serial.begin(9600);
  while (!Serial);
  // Init time and date
  rtc.begin(); // initialize RTC
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);
  // Check shield
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
  // init SPI and SD card
  SPI.begin();
  delay(100);
  if(!SD.begin(SD_CS_PIN)) {
    Serial.println("Failed to initialize SD card!");
    while (1);
  }
  // init the logfile
  getFileName();
  dataFile = SD.open(filename, FILE_WRITE);
  delay(1000);
  // init the CSV file with headers
  dataFile.println("date,time,temperature,humidity,pressure,illuminance");
  currentDay = rtc.getDay();
  // close the file
  dataFile.close();
  delay(100);
  Serial.println("Opened first file");
}

void loop() {
  actualDay = rtc.getDay();
  if (currentDay != actualDay)
  {
    // Add new file to SD at start of new dat
    getFileName();
    dataFile = SD.open(filename, FILE_WRITE);
    delay(1000);
    dataFile.println("date,time,temperature,humidity,pressure,illuminance");
    currentDay = actualDay;
    // close the file
    dataFile.close();
    delay(100);
    Serial.println("Opened a new file");
  }
  // init the logfile
  getFileName();
  dataFile = SD.open(filename, FILE_WRITE);
  delay(1000);
  // read all the sensor values
  temperature = ENV.readTemperature();
  humidity    = ENV.readHumidity();
  pressure    = ENV.readPressure();
  illuminance = ENV.readIlluminance();
  String time = (String(rtc.getHours())+":"+String(rtc.getMinutes())+":"+String(rtc.getSeconds()));
  String date = (String(rtc.getDay())+"/"+String(rtc.getMonth())+"/"+String(rtc.getYear()));
  // Save each of the sensor values to file
  dataFile.print(date);
  dataFile.print(",");
  dataFile.print(time);
  dataFile.print(",");
  dataFile.print(temperature);
  dataFile.print(",");
  dataFile.print(humidity);
  dataFile.print(",");
  dataFile.print(pressure);
  dataFile.print(",");
  dataFile.println(illuminance);
  // close the file
  dataFile.close();
  Serial.println("Added data to file");
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
  Serial.println();
  // wait 5 second to print again
  delay(5000);
}

void getFileName(){
  //Build a new filename
  filename[0] = rtc.getDay()/10 + '0'; //To get 1st digit from day()
  filename[1] = rtc.getDay()%10 + '0'; //To get 2nd digit from day()
  filename[2] = rtc.getMonth()/10 + '0'; //To get 1st digit from month()
  filename[3] = rtc.getMonth()%10 + '0'; //To get 2nd digit from month()
  filename[4] = rtc.getYear()/10 + '0'; //To get 3rd digit from year()
  filename[5] = rtc.getYear()%10 + '0'; //To get 4th digit from year()
  }
