/*--------------------------------------------------------------------
  De Slimme Meter
  Ths class reads and parses the Dutch Smart Meter

  Author Marcel Meek
  Date 12/7/2020

  Evert Versteeg
  Date 25/12/2020
  --------------------------------------------------------------------*/

#ifndef __DSM_H_
#define __DSM_H_
#include <Arduino.h>

#define BUF_SZ 1500

class Dsm {
  public:
    Dsm( Stream &port);
    bool read();
    void debug();

    uint32_t id;   // hashed meterid
    uint32_t tarief;
    float laag, hoog, laagTerug, hoogTerug, gas, power, powerTerug;  

  private:
    void parseMsg();
    void convertHexToBytes( char* dst, char* src);
    uint32_t jenkins_one_at_a_time_hash( char* key);
    Stream *p1;
    char buf[ BUF_SZ];
    int i;
}; 

#endif //_DSM_H_
