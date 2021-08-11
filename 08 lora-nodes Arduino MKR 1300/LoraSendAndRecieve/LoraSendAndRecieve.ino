/*

  Lora Send And Receive

  This sketch demonstrates how to send and receive data with the MKR WAN 1300/1310 LoRa module.

  This example code is in the public domain.

*/
#include <MKRWAN.h>
#include <CayenneLPP.h>
uint8_t size = 51;
CayenneLPP lpp(size);
LoRaModem modem;
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
  delay(300000);
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
  getFileName();
  readSensorValues();
  saveValuesToCard();
  printValuesToSerial();

  lpp.reset();
  lpp.addTemperature(1, temperature);
  lpp.addRelativeHumidity(2, humidity);
  lpp.addBarometricPressure(3, pressure*10);      //kPA => hPA
  lpp.addLuminosity(4, illuminance);

  Serial.print("Sending");
  int err;
  modem.beginPacket();
  modem.write(lpp.getBuffer(), lpp.getSize());
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
    Serial.println("Led LOW");            // Downlink 0x10 => Turn build in led "off"
    Serial.println();
      }
  if (payLoadDown == 2){
    digitalWrite(LED_BUILTIN, HIGH);      // Downlink 0x20 => Turn build in led "on"
    Serial.println("Led HIGH");
    Serial.println();
    }
  if (payLoadDown == 3){
    Serial.println("Restart modem");       // Downlink 0x30 => Restart Lora Modem
    Serial.println();
    delay(5000);
    modem.restart();
  }
}


//read all sensor values
void readSensorValues(){
  temperature = ENV.readTemperature();
  humidity    = ENV.readHumidity();
  pressure    = ENV.readPressure();
  illuminance = ENV.readIlluminance();
}


// Save sensor values to SD card in CSV file
void saveValuesToCard(){
  dataFile = SD.open(filename, FILE_WRITE);
  delay(1000);
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
  dataFile.print(pressure*10);    //kPA => hPA
  dataFile.print(",");
  dataFile.println(illuminance);
  // close the file
  dataFile.close();
}


// Print sensor values to serial interface
void printValuesToSerial(){
  Serial.println("Added data to file");
  // print each of the sensor values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity    = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Pressure    = ");
  Serial.print(pressure*10);      //kPA => hPA
  Serial.println(" hPa");
  Serial.print("Illuminance = ");
  Serial.print(illuminance);
  Serial.println(" lx");
  Serial.println();
}


//Build a new filename for a file on th SD card
void getFileName(){
  filename[0] = rtc.getDay()/10 + '0'; //To get 1st digit from day()
  filename[1] = rtc.getDay()%10 + '0'; //To get 2nd digit from day()
  filename[2] = rtc.getMonth()/10 + '0'; //To get 1st digit from month()
  filename[3] = rtc.getMonth()%10 + '0'; //To get 2nd digit from month()
  filename[4] = rtc.getYear()/10 + '0'; //To get 3rd digit from year()
  filename[5] = rtc.getYear()%10 + '0'; //To get 4th digit from year()
  }
