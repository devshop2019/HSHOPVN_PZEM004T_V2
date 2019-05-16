#ifndef HSHOP_VN_H_PZEM004T_V2_DEFINE_H_
#define HSHOP_VN_H_PZEM004T_V2_DEFINE_H_

#include "arduino.h"

#define MIROR_VALUE(x)        ((uint16_t)(((x<<8)&0xff00)+((x>>8)&0xff)))

#define SCALE_V               (0.1)
#define SCALE_A               (0.001)
#define SCALE_P               (0.1)
#define SCALE_E               (1)
#define SCALE_H               (0.1)
#define SCALE_PF              (0.01)

#define MAX_PZEM_TIMEOUT      (20000) //ms
#define MIN_PZEM_TIMEOUT      (1000) //ms

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

#endif
