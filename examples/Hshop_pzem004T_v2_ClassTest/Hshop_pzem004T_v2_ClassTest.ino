#include "Hshopvn_PZEM004T_V2.h"

Hshopvn_Pzem04t pzem1(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start! S(sf0 Serial");
  pzem1.begin(9600);
  pzem1.setTimeout(2000);
  
//  pzem1.resetEnergy();
}

void loop() {
  // put your main code here, to run repeatedly:
  pzem_info pzemData = pzem1.getData();

  Serial.print(pzemData.volt);
  Serial.print(F("V - "));
  Serial.print(pzemData.ampe);
  Serial.print(F("A - "));
  Serial.print(pzemData.power);
  Serial.print(F("W - "));
  Serial.print(pzemData.energy);
  Serial.print(F("Wh - "));
  Serial.print(pzemData.freq);
  Serial.print(F("Hz - "));
  Serial.print(pzemData.powerFactor);
  Serial.println();
  delay(1000);
  
}
