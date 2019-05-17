#include "Hshopvn_Pzem004t_V2.h"

byte getValue_para[8] = {0xf8, 0x04, 0x00, 0x00, 0x00, 0x0a, 0x64, 0x64};
byte resetEnergy_para[4] = {0xf8, 0x42, 0xc2, 0x41};

 Hshopvn_Pzem004t_V2::Hshopvn_Pzem004t_V2() {
  Serial.begin(9600);
  port = &Serial;
  typeSerial = HARD_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

Hshopvn_Pzem004t_V2::Hshopvn_Pzem004t_V2(HardwareSerial * serial) {
//  serial->begin(9600);
  port = serial;
  typeSerial = HARD_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

Hshopvn_Pzem004t_V2::Hshopvn_Pzem004t_V2(SoftwareSerial * serial) {
//  serial->begin(9600);
  port = serial;
  typeSerial = SOFT_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

Hshopvn_Pzem004t_V2::Hshopvn_Pzem004t_V2(int rxPin, int txPin) {
  SoftwareSerial * yy = new SoftwareSerial(rxPin, txPin);
//  yy->begin(9600);
  port = yy;
  typeSerial = SOFT_SERIAL;
  setTimeout(MIN_PZEM_TIMEOUT);
}

void Hshopvn_Pzem004t_V2::begin(unsigned long _tembaud) {
  if (typeSerial == HARD_SERIAL) {
    HardwareSerial * tt = (HardwareSerial *)port;
    tt->begin(_tembaud);
  } else {
    SoftwareSerial * tt = (SoftwareSerial *) port;
    tt->begin(_tembaud);
  }
}

void Hshopvn_Pzem004t_V2::begin() {
  this->begin(9600);
}

void Hshopvn_Pzem004t_V2::setTimeout(unsigned int _ui_timeOut) {
  if (_ui_timeOut < MIN_PZEM_TIMEOUT) {
    ui_timeOut = MIN_PZEM_TIMEOUT;
  } else if (_ui_timeOut > MAX_PZEM_TIMEOUT) {
    ui_timeOut = MAX_PZEM_TIMEOUT;
  } else
    ui_timeOut = _ui_timeOut;
}

pzem_info Hshopvn_Pzem004t_V2::getData(){
  pzem_info tem_pzem;
  while (port->available()) {
    port->read();
  }
  DB("port->write");
  port->write(getValue_para, sizeof(getValue_para));

  unsigned long temTime = millis();
  pzem_value pzemData;
  bool b_complete = false;

  while ((millis() - temTime) < ui_timeOut) {
    if (port->available()) {
      port->readBytes((byte*)&pzemData, sizeof(pzem_value));
      b_complete = true;
      DB("port->available");
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

    DB(tem_pzem.volt);    DB(F("V - "));
    DB(tem_pzem.ampe);    DB(F("A - "));
    DB(tem_pzem.power);    DB(F("W - "));
    DB(tem_pzem.energy);    DB(F("Wh - "));
    DB(tem_pzem.freq);    DB(F("Hz - "));
    DB_LN(tem_pzem.powerFactor);    DB(F(" - "));

  } else {
    DB_LN(F("Read fail"));
    tem_pzem.volt = 0.0;
    tem_pzem.ampe = 0.0;
    tem_pzem.power = 0.0;
    tem_pzem.energy = 0.0;
    tem_pzem.freq = 0.0;
    tem_pzem.powerFactor = 0.0;
  }
  return tem_pzem;
}

bool Hshopvn_Pzem004t_V2::resetEnergy() {
  bool status = false;
  while (port->available()) {
    port->read();
  }
  port->write(resetEnergy_para, sizeof(resetEnergy_para));

  unsigned long temTime = millis();
  pzem_value pzemData;
  bool b_complete = false;

  byte testRespone[4];

  while ((millis() - temTime) < ui_timeOut) {
    if (port->available()) {
      port->readBytes(testRespone, sizeof(testRespone));
      b_complete = true;
      DB(F("port->available"));
      break;
    }
  }

  if (b_complete) {
    if(testRespone[3] == resetEnergy_para[3]){
        status = true;
        DB_LN(F("resetEnergy success!"));
    }else{
        DB_LN(F("resetEnergy invalid"));
    }

  } else {
    DB_LN(F("read resetEnergy fail"));
    
  }
  return status;
}
