/*
 From: http://www.ccontrolsys.com/w/How_to_Compute_the_Modbus_RTU_Message_CRC

Using the 8 character ASCII input DEADBEEF (upper case)
the checksum is 0xDD18
The code below agrees with the online calculator here:
http://www.lammertbies.nl/comm/info/crc-calculation.html

*/

#define UInt16 uint16_t
// CRC should be DD18

//byte t[] = {0xf8, 0x04, 0x00, 0x00, 0x00, 0x0a};
byte t[] = {0xf8, 0x04, 0x14, 0x08, 0xc4, 0x00, 0x17, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf4, 0x00, 0x3c, 0x00, 0x00}; //F0FD
// ...01 f4 00 3c 00 00 fd f0
// Compute the MODBUS RTU CRC
UInt16 ModRTU_CRC(byte * buf, int len)
{
  UInt16 crc = 0xFFFF;
 
  for (int pos = 0; pos < len; pos++) {
    crc ^= (UInt16)buf[pos];          // XOR byte into least sig. byte of crc
 
    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;  
}

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  delay(1000);
  
  Serial.println(ModRTU_CRC(t,sizeof(t)),HEX);
}

void loop()
{

}
