/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#include "rover_ultrasonic.h"

RoverUltraSonic::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

unsigned long  RoverUltraSonic::measureDistance()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

bool RoverUltraSonic::isDistanceInArea(unsigned long distance_cm)
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}