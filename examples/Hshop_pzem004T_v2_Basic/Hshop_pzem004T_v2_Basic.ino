#include "Hshopvn_Pzem004t_V2.h"

Hshopvn_Pzem004t_V2 pzem1(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start Hshop test PZEM004T V2 !");
  pzem1.begin();
  pzem1.setTimeout(100);
  
//  bool rr;
//  rr = pzem1.resetEnergy();
//  if(rr){
//    Serial.println("reset Energy ok");
//  }
  
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
