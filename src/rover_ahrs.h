
/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
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
