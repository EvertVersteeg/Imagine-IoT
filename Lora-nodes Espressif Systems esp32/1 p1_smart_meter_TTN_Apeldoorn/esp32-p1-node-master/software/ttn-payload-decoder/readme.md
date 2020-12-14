# TTN payload decoder.
This is the payload decoder to be used with TTN.

## Installation
The payload decoder can be installed in the application at TTN console where the P1-Node is registerd by copying the file <a download="payload-decoder.js" href="payload-decoder.js" title="payload-decoder.js">payload-decoder.js</a>

## Description
The payload decoder provided with the P1-Node contains decoder functions for other projects of TTN-Apeldoorn. These projects or functions use their own port.

### Ports
The following ports are used in this payload-decoder:

Port  | Descripton
------|---------------------------------
11    | Position information for the Heatstress sensor of TTN-Apeldoorn
13    | System information of the Heatstress sensor of TTN-Apeldoorn
14    | Sensor values Heatstress sensor of TTN-Apeldoorn
40    | Smart meter information of the P1-Node of TTN Apeldoorn

### Implementation
<em>Unfortionately this code contains language specific terms in Dutch.</em>

The P1-Node reads from the intelligent energy meter the actual values and sends it over LoRaWAN.
In the following code snippet the following Dutch terms are used:

Dutch    | English
---------|--------------------
laag     | Energy used from the grid at low tarif
hoog     | Energy used from the grid at high tarif
laagterug| Energy delivered back to the grid at low tarif
hoogterug| Energy delivered back to the grid at high tarif


```
   case 40: 
      var meterid = bytesToHex( bytes);
      var laag = bytesToFloatLE( bytes.slice(4));
      var hoog = bytesToFloatLE( bytes.slice(8));
      var laagterug = bytesToFloatLE( bytes.slice(12));
      var hoogterug = bytesToFloatLE( bytes.slice(16));
      var gas = bytesToFloatLE( bytes.slice(20));
      
      return {
         "meterid": meterid,
         "laag": laag,
         "hoog": hoog,
         "laagterug": laagterug,
         "hoogterug": hoogterug,
         "gas": gas
      };
```
# License

The TTN-Apeldoorn P1-Node node is free soft- and hardware:
you can redistribute and/or modify it under the terms of a Creative Commons Attribution-NonCommercial 4.0 International License (http://creativecommons.org/licenses/by-nc/4.0/) by TTN-Apeldoorn (https://www.thethingsnetwork.org/community/apeldoorn/) E-mail: ttnapeldoorncoreteam@rfsee.nl

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">Creative Commons Attribution-NonCommercial 4.0 International License</a>.