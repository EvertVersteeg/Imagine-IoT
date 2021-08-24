/*
  Assignment v1.0
*/
#include <MKRWAN.h>
#include <CayenneLPP.h>
#include <Arduino_MKRENV.h>
#include <ArduinoLowPower.h>
#include "arduino_secrets.h"
#include "config.h"
#include <SPI.h>
#include <SD.h>
#include <RTCZero.h>
CayenneLPP lpp(size);
LoRaModem modem;
File dataFile;
RTCZero rtc;

//*****************************************************************************
// SETUP
//*****************************************************************************
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  //while (!Serial);
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }  
  // change this to your regional band (eg. US915, AS923, ...)
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  initCard();
  initLogFileOnCard();
  connectToLoRaWAN();
}

//*****************************************************************************
//LOOP
//*****************************************************************************
void loop() {
  checkForDayChange();  //Open a new logfile when a new day starts
  getFileName();        // Get the name of the latest file
  readSensorValues();
  saveValuesToCard();
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
  temperature = ENV.readTemperature();
  humidity    = ENV.readHumidity();
  pressure    = ENV.readPressure();
  illuminance = ENV.readIlluminance();
}


//*****************************************************************************
// Function: Save sensor values to SD card in CSV file
//*****************************************************************************
void saveValuesToCard(){
  dataFile = SD.open(filename, FILE_WRITE);
  delay(1000);
  String time = (String(rtc.getHours())+":"+String(rtc.getMinutes())+":"+String(rtc.getSeconds()));
  String date = (String(rtc.getDay())+"/"+String(rtc.getMonth())+"/"+String(rtc.getYear()));
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
  dataFile.close();
}


//*****************************************************************************
// Function: Print sensor values to serial interface
//*****************************************************************************
void printValuesToSerial(){
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
}


//*****************************************************************************
// Function: Put together the filename
//*****************************************************************************
void getFileName(){
  filename[0] = rtc.getDay()/10 + '0'; //To get 1st digit from day()
  filename[1] = rtc.getDay()%10 + '0'; //To get 2nd digit from day()
  filename[2] = rtc.getMonth()/10 + '0'; //To get 1st digit from month()
  filename[3] = rtc.getMonth()%10 + '0'; //To get 2nd digit from month()
  filename[4] = rtc.getYear()/10 + '0'; //To get 3rd digit from year()
  filename[5] = rtc.getYear()%10 + '0'; //To get 4th digit from year()
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
  lpp.addTemperature(1, temperature);
  lpp.addRelativeHumidity(2, humidity);
  lpp.addBarometricPressure(3, pressure*10);      //kPA => hPA
  lpp.addLuminosity(4, illuminance);
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


//*****************************************************************************
// Function: Check if new day started => open a new file
//*****************************************************************************
void checkForDayChange(){
  actualDay = rtc.getDay();
  if (currentDay != actualDay)
  {
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
}

//*****************************************************************************
// Function: Init the memory card
//*****************************************************************************
void initCard(){
  rtc.begin(); // initialize RTC
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);
  // init SPI and SD card
  SPI.begin();
  delay(100);
  if(!SD.begin(SD_CS_PIN)) {
    Serial.println("Failed to initialize SD card!");
    while (1);
  }
}
//*****************************************************************************
// Function: Init log file on memorycard
//*****************************************************************************
void initLogFileOnCard(){
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
}
