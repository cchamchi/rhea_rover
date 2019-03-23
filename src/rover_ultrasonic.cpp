/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#include "rover_ultrasonic.h"

RoverUltraSonic::RoverUltraSonic(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  _trigPin = trigPin;
  _echoPin = echoPin;
}

unsigned long  RoverUltraSonic::measureDistance()
{
  digitalWrite(trigPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  unsigned long duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  distance = ((float)(340 * duration) / 10000) / 2;  
}

bool RoverUltraSonic::isDistanceInArea(unsigned long distance_cm)
{
  if(){
    //not dangerous
    return true;
  }else{
    //too close
    return false;
  }
  //turn around
  
  
}