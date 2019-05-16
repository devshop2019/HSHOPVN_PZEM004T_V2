#ifndef _HSHOP_VN_H_PZEM004T_V2_H__
#define _HSHOP_VN_H_PZEM004T_V2_H__

#include "arduino.h"
#include "Hshopvn_PZEM004T_V2_define.h"
#include "SoftwareSerial.h"

enum {
  HARD_SERIAL,
  SOFT_SERIAL
};

#define writeToSerial(...)      { port->write(__VA_ARGS__); }

//#define EN_DEBUG_HSHOP_VN_PZEM004TV2

#if defined(EN_DEBUG_HSHOP_VN_PZEM004TV2)
  #define debug                   Serial
  #define DB(...)                 debug.print(__VA_ARGS__);
  #define DB_LN(...)              debug.println(__VA_ARGS__);
#else
  #define debug                   Serial
  #define DB(...)                 
  #define DB_LN(...)              
#endif

extern byte getValue_para[8];
extern byte resetEnergy_para[4];

class Hshopvn_Pzem04t{
  private:
    uint8_t typeSerial;
    Stream * port;
    unsigned int ui_timeOut;
    
  public:
     Hshopvn_Pzem04t();

    virtual ~Hshopvn_Pzem04t(){delete port;}

    Hshopvn_Pzem04t(HardwareSerial * serial);

    Hshopvn_Pzem04t(SoftwareSerial * serial);

    Hshopvn_Pzem04t(int rxPin, int txPin);

    void begin(unsigned long _tembaud);

    void setTimeout(unsigned int _ui_timeOut);

    pzem_info getData();

    void resetEnergy();
};

#endif
