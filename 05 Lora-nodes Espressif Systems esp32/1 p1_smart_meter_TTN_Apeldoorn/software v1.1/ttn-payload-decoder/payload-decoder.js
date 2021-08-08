// 10/5/2020:  Payload format Buitenbuurt
// MM copied from Hittestress project.

// 25/8/2020 Payload decoder for "De Slimme Meter" added
// by Marcel Meek

function Decoder(bytes, port) {

// bytes to float little endian
  function bytesToFloatLE(bytes) {
    var bits = bytes[3]<<24 | bytes[2]<<16 | bytes[1]<<8 | bytes[0];
    var sign = (bits>>>31 === 0) ? 1.0 : -1.0;
    var exponent = bits>>>23 & 0xff;
    var mantisse = (exponent === 0) ? (bits & 0x7fffff)<<1 : (bits & 0x7fffff) | 0x800000;
    var floating_point = sign * mantisse * Math.pow(2, exponent - 127) / 0x800000;
    return floating_point;
  }

  function bytesToHex( bytes) {
    var hex = bytes[3].toString(16);
    hex += bytes[2].toString(16);
    hex += bytes[1].toString(16);
    hex += bytes[0].toString(16);
    return hex.toUpperCase();
  }


// bytes to float big endian
   function bytesToFloat(bytes) {
     var bits = bytes[0]<<24 | bytes[1]<<16 | bytes[2]<<8 | bytes[3];
     var sign = (bits>>>31 === 0) ? 1.0 : -1.0;
     var exponent = bits>>>23 & 0xff;
     var mantisse = (exponent === 0) ? (bits & 0x7fffff)<<1 : (bits & 0x7fffff) | 0x800000;
     var floating_point = sign * mantisse * Math.pow(2, exponent - 127) / 0x800000;
     return floating_point;
   }

   function bytesToInt16(bytes) {
     var val = bytes[0]<<8 | bytes[1];
     return (val < 0x8000) ? val : val - 0x10000;
   }
  
   function bytesToInt32(bytes) {
      var val = bytes[0]<<24 | bytes[1]<<16 | bytes[2]<<8 | bytes[3];
     return (val < 0x80000000) ? val : val - 0x10000000;
   }
   
   function bytesToInt64(bytes) {
     var int32_m = bytes[0]<<24 | bytes[1]<<16 | bytes[2]<<8 | bytes[3];
     var int32_l = bytes[4]<<24 | bytes[5]<<16 | bytes[6]<<8 | bytes[7];
     return int32_m<<32 | int32_l;
   }


// code starts here
switch(port) {

// Convert GPS info and Version from Hittestress sensor
  case 0xB:  
    var lat= bytesToInt32(bytes.slice(0))/10000000;
    var lon = bytesToInt32(bytes.slice(4))/10000000;
    var alt = bytesToInt16(bytes.slice(8));
    var hdop = bytesToInt16(bytes.slice(10))/1000;
    var SwVer = bytes.slice(12)[0];

    return {
          //lat: lat,
          //lon: lon, 
          latitude: lat,
          longitude: lon, 
          alt: alt,
          hdop: hdop,
          SwVer: SwVer
     } ;
     
// Convert status info from Hittestress sensor
  case 0xD:
    return {
       CpuTemp  : bytesToInt16(bytes.slice(0))/10, 
       Vbat : bytesToInt16(bytes.slice(2))/100, 
       LowBat: bytes.slice(4) & 0x01 ,
     } ;

// Convert dust, temperature and Humidity values from Hittestress sensor
  case 0xE: 
    return {
       pm2p5: bytesToInt16(bytes.slice(0))/10, 
       pm10 : bytesToInt16(bytes.slice(2))/10, 
       rh   : bytesToInt16(bytes.slice(4))/10, 
       temp : bytesToInt16(bytes.slice(6))/10,
     } ;
  
// Convert values from "De Slimme Meter"
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
  }
  return {};
}
