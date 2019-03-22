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
  ahrsBegin();
  _ahrs_data_flag=false;
}
void RoverAhrs::update()
{
  if(isAhrsDataReady()){
    readAhrsData();
    caculrateMotionAcceleration();
    _ahrs_data_flag=true;
  }
}
GyroInfo RoverAhrs::getGyro()
{
  GyroInfo gyro;
  gyro.roll=roll;
  gyro.pitch=pitch;
  gyro.yaw=yaw;
  return gyro;
}
AcceleroInfo RoverAhrs::getAccelero()
{
  AcceleroInfo accelero;
  accelero.ax=ax;
  accelero.ay=ay;
  accelero.az=az;
  return accelero;
}
float RoverAhrs::getMotionAcceleration()
{
  return _motion_acceleration;
}

void RoverAhrs::caculrateMotionAcceleration()
{
  float x,y,z;
  x=ax;
  y=ay;
  z=az;

  _motion_acceleration=pow( (x*x+y*y+z*z),0.5);
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

void RoverAhrs::rx_empty(){
  rx_empty();
}

void RoverAhrs::printAhrsInfo()
{
  if(_print_count>=10){
    Serial.println(F("++++  AHRS Info   +++++++++++++++"));
    Serial.println(F("r/p/y/x/y/z= "));
    Serial.print(roll,1);Serial.print(F(","));
    Serial.print(pitch,1);Serial.print(F(","));
    Serial.print(yaw,1);Serial.print(F(","));
    Serial.print(ax,1);Serial.print(F(","));
    Serial.print(ay,1);Serial.print(F(","));
    Serial.println(az,1);

    Serial.print(F("motionAcc= "));
    Serial.println(_motion_acceleration,3);
    //Serial.println(F("++++++++++++++++++++++++++++++++++"));
    _print_count=0;
 }
 _print_count++;

}

void RoverAhrs::readAhrsData()
{
  roll=_sbuf[0];
  pitch=_sbuf[1];
  yaw=_sbuf[2];
  ax=_sbuf[3];
  ay=_sbuf[4];
  az=_sbuf[5];

}
/* 여기부분은 어떻게 해야되는지 모르겠어요 ㅠㅠ
bool RoverAhrs::isAhrsDataReady()
{
  bool ready;
  ready;

  if(cansatIMU.read(_sbuf,6)){

    ready=true;
  }else{
    ready=false;
  }

  return ready;
}
*/
