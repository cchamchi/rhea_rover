/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#include "rover_PM2_5.h"
#include "Arduino.h"


rover_PM2_5::PM2_5(int Vo, int V_LED){
  _Vo=Vo;
  _V_LED=V_LED;
  
  pinMode(_V_LED,OUTPUT);
  pinMode(_Vo,INPUT);
}
void rover_PM2_5::rover_PM2_5loop(){
  digitalWrite(V_LED,LOW);
  delayMicroseconds(280);
  Vo_value =analogRead(Vo);
  delayMicroseconds(40);
  digitalWrite(V_LED,HIGH);
  delayMicroseconds(9680);
  voltage = Vo_value*5.0/1024.0;
  dustDensity = (voltage-0.3)/0.005;
  if(dustDensity<0){
    Serial.println("Waiting...");
  }
  if(dustDensity<30){
    Serial.println("What a NICE Air!");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }
  else if(dustDensity<80){
    Serial.println("It's GOOD.");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }
  else if(dustDensity<150){
    Serial.println("It's pretty BAD. Please keep your child from going out.");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }
  else{
    Serial.println("DO NEVER GO OUT!");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }  
  
  delay(1000);
}
