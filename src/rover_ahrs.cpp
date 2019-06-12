/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#include "rover_ahrs.h"



void RoverAhrs::begin()
{
  Wire.begin();
  //initiate MPU6050
  initialize();
  _ahrs_data_flag=false;
}
void RoverAhrs::update()
{
  // read raw accel/gyro measurements from device
  getMotion6(&ax, &ay, &az, &roll, &pitch, &yaw);
  caculrateMotionAcceleration();
}


void RoverAhrs::caculrateMotionAcceleration()
{
  float x,y,z;
  x=(float)ax/32767.;
  y=(float)ay/32767.;
  z=(float)az/32767.;

  motion_acceleration=pow( (x*x+y*y+z*z),0.5);
}

bool RoverAhrs::isAhrsDataNew()
{
  if(_ahrs_data_flag){
    _ahrs_data_flag=false;
    return(true);
  }else{
    return(false);
  }

}

