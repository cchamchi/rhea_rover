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

struct AhrsInfo {
  float roll;
  float pitch;
  float yaw;
  float ax;
  float ay;
  float az;
};
struct GyroInfo {
  float roll;
  float pitch;
  float yaw;
};
struct AcceleroInfo {
  float ax;
  float ay;
  float az;
};

class RoverAhrs
{
  public:
    void readAhrsData();
    bool isAhrsDataReady();
    void ahrsBegin();
    void rx_empty();

    float roll;
    float pitch;
    float yaw;
    float ax;
    float ay;
    float az;
    
    void begin();
    void update();
    GyroInfo getGyro();
    AcceleroInfo getAccelero();
    float getMotionAcceleration();
    void caculrateMotionAcceleration();

    bool isAhrsDataNew();
    void printAhrsInfo();

  private:
    float _sbuf[6];

    bool _ahrs_data_flag;
    float _motion_acceleration;
    int _print_count;
};


#endif
