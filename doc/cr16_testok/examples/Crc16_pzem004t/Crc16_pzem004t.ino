#include "Crc16.h"
Crc16 crc; 

void setup()
{
    Serial.begin(38400); 
    Serial.println("CRC-16 bit test program");
    Serial.println("=======================");
}

int sizess = 0;
void loop()
{
  /*
    Examples of crc-16 configurations
    Kermit: width=16 poly=0x1021 init=0x0000 refin=true  refout=true  xorout=0x0000 check=0x2189
    Modbus: width=16 poly=0x8005 init=0xffff refin=true  refout=true  xorout=0x0000 check=0x4b37
    XModem: width=16 poly=0x1021 init=0x0000 refin=false refout=false xorout=0x0000 check=0x31c3
    CCITT-False:width=16 poly=0x1021 init=0xffff refin=false refout=false xorout=0x0000 check=0x29b1
    see http://www.lammertbies.nl/comm/info/crc-calculation.html
  */

  unsigned long ttt = micros();
  //calculate crc incrementally
//  byte data[] = "123456789";
//  byte data[] = {0xf8, 0x03, 0x0e, 0x00, 0x01, 0x59, 0xd8, 0x00, 0x01, 0x25, 0x80, 0x08, 0x98, 0x27, 0x10, 0x55, 0xf0};
//  byte data[] = {0xf8, 0x42};
  byte data[] = {0xf8, 0x04, 0x00, 0x00, 0x00, 0x0a};
  
//  Serial.println("Calculating crc incrementally");
  
  crc.clearCrc();
  sizess = sizeof(data);
  for(byte i=0;i<sizess;i++)
  {
//     Serial.print("byte ");
//     Serial.print(i);
//     Serial.print(" = ");
//     Serial.println(data[i]);
     crc.updateCrc(data[i]);
  }
  unsigned short value;
  //Modbus
  value = crc.Modbus(data,0,sizess);
  ttt = micros() - ttt;
  Serial.print("Modbus crc = 0x");    
  Serial.println(value, HEX);

  Serial.print("Delay: ");    
  Serial.println(ttt);
  delay(1000);
}
//Check routine taken from
//http://web.mit.edu/6.115/www/miscfiles/amulet/amulet-help/xmodem.htm
//int calcrc(char *ptr, int count)
//{
//    int  crc;
//    char i;
//    crc = 0;
//    while (--count >= 0)
//    {
//        crc = crc ^ (int) *ptr++ << 8;
//        i = 8;
//        do
//        {
//            if (crc & 0x8000)
//                crc = crc << 1 ^ 0x1021;
//            else
//                crc = crc << 1;
//        } while(--i);
//    }
//    return (crc);
//}
