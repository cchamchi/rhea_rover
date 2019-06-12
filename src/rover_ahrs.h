
/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/
// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

#ifndef RoverAHRS_h
#define RoverAHRS_h

#include "Arduino.h"

//========================== MPU6050
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define OUTPUT_READABLE_ACCELGYRO                                                         
//========================== MPU6050

struct AhrsInfo {
  int16_t roll;
  int16_t pitch;
  int16_t yaw;
  int16_t ax;
  int16_t ay;
  int16_t az;
};
struct GyroInfo {
  int16_t roll;
  int16_t pitch;
  int16_t yaw;
};
struct AcceleroInfo {
  int16_t ax;
  int16_t ay;
  int16_t az;
};


class RoverAhrs : public MPU6050 {
  public:
    RoverAhrs():MPU6050(),roll(0),pitch(0),yaw(0),ax(0),ay(0),az(0)
    {}
 
    void begin();
    void update();
    void caculrateMotionAcceleration();
    bool isAhrsDataNew();

    int16_t roll;
    int16_t pitch;
    int16_t yaw;
    int16_t ax;
    int16_t ay;
    int16_t az;
    float motion_acceleration;

  private:    
    bool _ahrs_data_flag;
    int _print_count;
};


#endif
