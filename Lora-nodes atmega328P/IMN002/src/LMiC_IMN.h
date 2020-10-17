/*
Library voor de Imagine-Node

Imagine Solutions BV 
rev. 11-9-2019
http://www.imagineiot.nl

Evert Versteeg
*/

// Libraries toevoegen
#include <lmic.h>                                               // LoRaMAC in C Library versie 1.5  => https://github.com/matthijskooijman/arduino-lmic
#include <hal/hal.h>                                            // Hardware Abstraction Layer Library   => https://github.com/matthijskooijman/arduino-lmic
#include <CayenneLPP.h>                                         // Cayenne Low Power Payload => https://www.thethingsnetwork.org/docs/devices/arduino/api/cayennelpp.html
#include <SPI.h>                                                // SPI bus library tbv LoRaRadio => 
#include <avr/eeprom.h>                                         // Library tbv wegschijven keys in eeprom van de Athmel 328p CPU

// Vastleggen definities
#define MAX_SIZE 51                                             // Maximale groote van de Payload => 51 bytes is safe                                   
#define DEBUG true                                              // Schakelen debug mode
#define LED_PIN        21                                       // Pin definitie waar LED op is aangesloten
uint8_t downLinkbyte1 = 0;
uint8_t downLinkbyte2 = 0;
uint8_t downLinkbyte3 = 0;
uint8_t downLinkbyte4 = 0;


// Instanties maken
CayenneLPP Payload(MAX_SIZE);                                   // Vastleggen maximale grote payload

                                            // Output D21 definitie voor LED

// Constanten aanmaken
const uint32_t TX_TIMEOUT = 60000;                              // Try transmission for up to 60 seconds (this includes joining)
const lmic_pinmap lmic_pins = {                                 // Pin mapping LoRaRadio
    .nss = 10,                                                  // nss is aangesloten op D10 van de CPU => pin 5 van de LoRaRadio (Hoperf)
    .rxtx = LMIC_UNUSED_PIN,                                    // Niet gebruikt
    .rst = 9,                                                   // reset is aangesloten op D09 van de CPU => pin 6 van de LoRaRadio
    .dio = {2, 3, 4},                                           // SPI mapping, D11 (MOSI), D12(MISO), D13(CSK) => pin 3, 2 en 4 van de LoRaRadio
};

// ------------------------------
// Event function
// ------------------------------
ev_t waitingForEvent = (ev_t)0;                                 // opstarten eventafhandeling

void onEvent (ev_t ev) {
  if (waitingForEvent == ev)
    waitingForEvent = (ev_t)0;
  if (DEBUG) {                                                  // Debug meldingen gekoppeld aan events
    Serial.print((uint32_t)os_getTime());
    Serial.print(": ");
    switch (ev) {
      case EV_SCAN_TIMEOUT:                                     
        Serial.println(F("EV_SCAN_TIMEOUT"));
        break;
      case EV_BEACON_FOUND:
        Serial.println(F("EV_BEACON_FOUND"));
        break;
      case EV_BEACON_MISSED:
        Serial.println(F("EV_BEACON_MISSED"));
        break;
      case EV_BEACON_TRACKED:
        Serial.println(F("EV_BEACON_TRACKED"));
        break;
      case EV_JOINING:
        LMIC_setDrTxpow(DR_SF9, 14);                               // Let join start at SF9, since that's what we'll be using for transmission anyway
        Serial.println(F("EV_JOINING"));
        break;
      case EV_JOINED:
        Serial.println(F("EV_JOINED"));
        LMIC_setLinkCheckMode(0);                                  // Disable link check validation
        pinMode(LED_PIN, OUTPUT);
        for (uint8_t i=0; i<10; i++) {                             // Led laten knipperen indien Joined
          digitalWrite(LED_PIN, HIGH);
          delay(200);
          digitalWrite(LED_PIN, LOW);
          delay(100);
        }
        break;
      case EV_RFU1:
      Serial.println(F("EV_RFU1"));
        break;
      case EV_JOIN_FAILED:
        Serial.println(F("EV_JOIN_FAILED"));
        break;
      case EV_REJOIN_FAILED:
        Serial.println(F("EV_REJOIN_FAILED"));
        break;
      case EV_TXCOMPLETE:
        Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
        if (LMIC.txrxFlags & TXRX_ACK)
          Serial.println(F("Received ack"));
          
        if (LMIC.dataLen) 
        {
          Serial.println(F("Received "));
          Serial.print(LMIC.dataLen);
          Serial.println(F(" bytes of payload"));
          
          Serial.print("[");
          for (uint8_t i=0; i < LMIC.dataLen; i++)
          {
            //Serial.print(LMIC.frame[i]);
            Serial.print(LMIC.frame[LMIC.dataBeg+i]);
            downLinkbyte1 = LMIC.frame[LMIC.dataBeg];
            downLinkbyte2 = LMIC.frame[LMIC.dataBeg+1];
            downLinkbyte3 = LMIC.frame[LMIC.dataBeg+2];
            downLinkbyte4 = LMIC.frame[LMIC.dataBeg+3];
            Serial.print(" ");
          }
          Serial.println("]");
        }
        break;
      case EV_LOST_TSYNC:
        Serial.println(F("EV_LOST_TSYNC"));
        break;
      case EV_RESET:
        Serial.println(F("EV_RESET"));
        break;
      case EV_RXCOMPLETE:
        // data received in ping slot
        Serial.println(F("EV_RXCOMPLETE"));
        break;
      case EV_LINK_DEAD:
        Serial.println(F("EV_LINK_DEAD"));
        break;
      case EV_LINK_ALIVE:
        Serial.println(F("EV_LINK_ALIVE"));
        break;
      default:
        Serial.println(F("Unknown event"));
        break;
    }
  }
}

// ------------------------------
// Event function
// ------------------------------

void imn_lmic_setup() {
  os_init();                                                                        // LMIC init
  LMIC_reset();                                                                     // Reset the MAC state. Session and pending data transfers will be discarded.
  // TTN defines an additional channel at 869.525Mhz using SF9 for class B device ping slots. LMIC does not have an easy way to define set this
  // Frequency and support for class B is spotty and untested, so this frequency is not configured here.
  LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
  LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
  LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
  LMIC_setAdrMode(1);
  LMIC_setLinkCheckMode(1);
  LMIC_setClockError(MAX_CLOCK_ERROR * 5 / 100);                                    // Let LMIC compensate for +/- 2% clock error changed 2->5
}

void imn_lmic_wait_for_txcomplete() {
  waitingForEvent = EV_TXCOMPLETE;
  uint32_t start = millis();
  while(waitingForEvent && millis() - start < TX_TIMEOUT)
    os_runloop_once();
  // if (DEBUG) {
    //if (waitingForEvent)
      //Serial.println(F("Transmit timeout"));
   // else
   //   Serial.println(F("Transmit complete"));
 // }
}