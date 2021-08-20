// All config setting

// chip select for SD card
const int SD_CS_PIN = 4;

// LED on IO 5
#define LED 5

// default sensor values
float temperature = 0;
float humidity    = 0;
float pressure    = 0;
float illuminance = 0;
int statusLed = 0;

/* Change these values to set the current initial date */
const byte seconds = 0;
const byte minutes = 10;
const byte hours = 16;
const byte day = 10;
const byte month = 8;
const byte year = 21;
char filename[] = "000000.CSV";
byte actualDay =0;
byte currentDay =0;

// Cayenne size
uint8_t size = 51;

// Variable for storing the downlink message
int payLoadDown = 0;
