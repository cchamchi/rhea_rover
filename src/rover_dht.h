/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/



#ifndef RoverDHT_h
#define RoverDHT_h

#include "Arduino.h"

class RoverDht
{
  public:
    Morse(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};


#endif