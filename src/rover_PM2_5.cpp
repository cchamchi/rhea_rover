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


RoverPM2_5::RoverPM2_5(int Vo, int V_LED){
  _Vo=Vo;
  _V_LED=V_LED;
  _dustDensity = 0;
  _last_millis=0;
}
void RoverPM2_5::begin(){
  pinMode(_V_LED,OUTPUT);
}
float RoverPM2_5::calulatePM2_5(){
  float Vo_value,voltage;
  long current_millis=millis();
  if((_last_millis-current_millis) > SLEEP_TIME ){
    _last_millis=current_millis;
    digitalWrite(_V_LED,LOW);  //power on LED
    delayMicroseconds(SAMPLING_TIME);

    Vo_value =analogRead(_Vo); //read a dust Vo_value

    delayMicroseconds(DELTA_TIME);
    digitalWrite(_V_LED,HIGH); //turn off LED
    //delayMicroseconds(SLEEP_TIME);

    voltage = Vo_value*(5.0/1024.0);  // 0 - 5V mapped to 0 - 1023 integer values
    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    //_dustDensity = (voltage-0.3)/0.005;// where are you from?
    _dustDensity = 0.17 * voltage - 0.1;

    return _dustDensity;
  }else{
    Serial.println(F("update need at least 1second "));
    _last_millis=current_millis;
    return(-1);
  }
}