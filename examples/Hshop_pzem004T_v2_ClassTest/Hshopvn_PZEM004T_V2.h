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

#define debug                   Serial
#define DB(...)                 debug.print(__VA_ARGS__);
#define DB_LN(...)              debug.println(__VA_ARGS__);


extern byte getValue_para[8];
extern byte resetEnergy_para[4];

class Hshopvn_Pzem04t {
  public:
    uint8_t typeSerial;
    Stream * port;

    inline Hshopvn_Pzem04t() {
      port = &Serial;
      typeSerial = HARD_SERIAL;
    }

    inline Hshopvn_Pzem04t(HardwareSerial * serial) {
      port = serial;
      typeSerial = HARD_SERIAL;
    }

    inline Hshopvn_Pzem04t(SoftwareSerial * serial) {
      port = serial;
      typeSerial = SOFT_SERIAL;
    }

    inline Hshopvn_Pzem04t(int rxPin, int txPin) {
      SoftwareSerial * yy = new SoftwareSerial(rxPin, rxPin);
      port = yy;
      typeSerial = SOFT_SERIAL;
    }

    inline void begin(unsigned long _tembaud) {
      if (typeSerial == HARD_SERIAL) {
        HardwareSerial * tt = port;
        tt->begin(_tembaud);
      } else {
        SoftwareSerial * tt = port;
        tt->begin(_tembaud);
      }
    }

    void getData() {
      //      if (port->available()) {
      //        port->println(port->read(), HEX);
      //        char uu[4] = "1234";
      //        write(uu, 4);
      //      }
      pzem_info tem_pzem;
      while (port->available()) {
        port->read();
      }
      port->write(getValue_para, sizeof(getValue_para));

      unsigned long temTime = millis();
      pzem_value pzemData;
      bool b_complete = false;

      while ((millis() - temTime) < 20000) {
        if (port->available()) {
          port->readBytes((byte*)&pzemData, sizeof(pzem_value));
          b_complete = true;
          break;
        }
      }

      if (b_complete) {
        tem_pzem.volt = (float)MIROR_VALUE(pzemData.voltage_int) * SCALE_V;
        tem_pzem.ampe = (float)MIROR_VALUE(pzemData.ampe_int) * SCALE_A;
        tem_pzem.power = (float)MIROR_VALUE(pzemData.power_int) * SCALE_P;
        tem_pzem.energy = (float)MIROR_VALUE(pzemData.energy_int) * SCALE_E;
        tem_pzem.freq = (float)MIROR_VALUE(pzemData.freq_int) * SCALE_H;
        tem_pzem.powerFactor = (float)MIROR_VALUE(pzemData.powerFactor_int) * SCALE_PF;

        DB(tem_pzem.volt);    DB("V - ");
        DB(tem_pzem.ampe);    DB("A - ");
        DB(tem_pzem.power);    DB("W - ");
        DB(tem_pzem.energy);    DB("Wh - ");
        DB(tem_pzem.freq);    DB("Hz - ");
        DB_LN(tem_pzem.powerFactor);    DB(" - ");

      } else {
        DB_LN("Read fail");
      }
      return tem_pzem;
    }

    void reset_Energy() {
      while (port->available()) {
        port->read();
      }
      port->write(resetEnergy_para, sizeof(resetEnergy_para));
    }
};



#endif
