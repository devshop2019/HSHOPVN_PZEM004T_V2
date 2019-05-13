#include "SoftwareSerial.h"

SoftwareSerial pzem(2,3);
#define debug     Serial
#define DB(x)  debug.print(x);
#define DB_LN(x)  debug.println(x);

//#define MIROR_VALUE(x)      ((uint16_t)((x<<8)+(x>>8) & 0xff))
#define MIROR_VALUE(x)      ((uint16_t)(((x<<8)&0xff00)+((x>>8)&0xff)))

#define SCALE_V       (0.1)
#define SCALE_A       (0.001)
#define SCALE_P       (0.1)
#define SCALE_E       (1)
#define SCALE_H       (0.1)
#define SCALE_PF      (0.01)

byte getValue_para[]={0xf8,0x04, 0x00, 0x00, 0x00, 0x0a, 0x64, 0x64};

typedef struct pzem_info{
  float volt;
  float ampe;
  float power;
  float energy;
  float freq;
  float powerFactor;
  
};

typedef struct pzem_value{
  byte address;
  byte byteSuccess;
  byte numberOfByte;
  int voltage_int; 
  int ampe_int;
  int nouse1;
  int power_int;
  int nouse2;
  int energy_int;
  int nouse3;
  int freq_int;
  int powerFactor_int;
  int nouse4;
  int crc_int; 
};

void setup() {
  // put your setup code here, to run once:
  pzem.begin(9600);
  debug.begin(9600);
  DB_LN("Start debug");
  sendCommand();
}

pzem_info sendCommand(){
  pzem_info tem_pzem;
  while(pzem.available()){
    pzem.read();
  }
  pzem.write(getValue_para, sizeof(getValue_para));

  unsigned long temTime = millis();
  pzem_value pzemData;
  bool b_complete = false;
  
  while((millis() - temTime)<20000){
    if(pzem.available()){    
      pzem.readBytes((byte*)&pzemData, sizeof(pzem_value));
      b_complete = true;
      break;
    }
  }

  if(b_complete){
    float value = (float)MIROR_VALUE(pzemData.voltage_int)* 0.1;

    tem_pzem.volt = (float)MIROR_VALUE(pzemData.voltage_int)* SCALE_V;
    tem_pzem.ampe = (float)MIROR_VALUE(pzemData.ampe_int)* SCALE_A;
    tem_pzem.power = (float)MIROR_VALUE(pzemData.power_int)* SCALE_P;
    tem_pzem.energy = (float)MIROR_VALUE(pzemData.energy_int)* SCALE_E;
    tem_pzem.freq = (float)MIROR_VALUE(pzemData.freq_int)* SCALE_H;
    tem_pzem.powerFactor = (float)MIROR_VALUE(pzemData.powerFactor_int)* SCALE_PF;

    DB(tem_pzem.volt);    DB("V - ");
    DB(tem_pzem.ampe);    DB("A - ");
    DB(tem_pzem.power);    DB("W - ");
    DB(tem_pzem.energy);    DB("Wh - ");
    DB(tem_pzem.freq);    DB("Hz - ");
    DB_LN(tem_pzem.powerFactor);    DB(" - ");
    
    
//    DB_LN("Volt: " + String(pzemData.voltage_int, HEX)+" pf: " + String(value));
//    DB_LN("Volt: " + String(pzemData.voltage_int, HEX)+" pf: " + String(MIROR_VALUE(pzemData.powerFactor_int), HEX));
    
  }else{
    DB_LN("Read fail");
  }
  return tem_pzem;
}
void loop() {
  // put your main code here, to run repeatedly:

}

/*
f8 04 00 00 00 0a 64 64

f8 04 14     08 d3        00 23       00 00       00 05     00 00     00 02   00 00     01 f5       00 06       00 00 f8 be

            225.9v -      0.035a -                0.5W  -             2Wh -             50.1hZ  -   0.06POWERFactor
*/

