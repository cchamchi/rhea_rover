/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#ifndef RoverUltraSonic_h
#define RoverUltraSonic_h

#include "Arduino.h"

class RoverUltraSonic
{
  public:
    Morse(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};


#endif