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


rover_PM2_5::rover_PM2_5(int Vo, int V_LED){
  _Vo=Vo;
  _V_LED=V_LED;
  
  pinMode(_V_LED,OUTPUT);
  pinMode(_Vo,INPUT);
}
rover_PM2_5::rover_PM2_5(int Vo){
  _Vo=Vo;
  pinMode(_Vo,INPUT);
}

void rover_PM2_5::calulatePM2_5(float _dustDensity){
  digitalWrite(_V_LED,LOW);
  delayMicroseconds(280);
  Vo_value =analogRead(_Vo);
  delayMicroseconds(40);
  digitalWrite(_V_LED,HIGH);
  delayMicroseconds(9680);
  voltage = Vo_value*5.0/1024.0;
  _dustDensity = (voltage-0.3)/0.005;

  return _dustDensity;
}