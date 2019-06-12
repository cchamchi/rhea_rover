#include <CmdMessenger.h>  // CmdMessenger

#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_PM2_5.h"
#include "src/rover_SD.h"
#include "src/rover_MQ7.h"
#include "src/rover_sht.h"
/* software serial pin map */
// GPS : 8,9
// BLE : 4,5
// Lx16A : 6,7
// SD : 13,12,11,10
// MQ7 carbon Monoxide:  A0
// UltraSonic : 4,5     // BLE or UltraSonic
// PM2.5 :  A1, 3
// RF communication :
//  SHT3x : I2C 0x45
// MPU6050 : I2C 0x68 

int joy_velocity=0,joy_raduis=0;
int v=0;

CmdMessenger cmdMessenger = CmdMessenger(Serial);
RoverSD roverSd;
RoverMQ7 roverMQ7(A0,5.0);

void setup() {

  
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(9600);
  pirintLogo();  
  setupRoverGps();

  setupSHT3x();
  //setupRoverAhrs();
  Serial.println("Setup Start!");
  setupRoverMotor();
  Serial.println("Setup Complete!");
  //setupJoystick();
  
  //setup SD
  roverSd.begin(10);

  //setup Command Messenger 
  attachCommandCallbacks();
  cmdMessenger.printLfCr();

}

void loop() {
  //loopRoverAhrs();
  //loopRoverGps(); 
   //loopJoystick();
  // put your setup code here, to run once:
  
  //setupRoverGps();
  //loopUltraSonicTest();
  //read carbon monoxide value
  //Serial.println(roverMQ7.getPPM());

  Serial.println("Loop Start");
  RoverMotorTest();
  Serial.println("Loop Passed");
  //Serial.println("dd");
  updateRoverPM2_5(); //this fucntion need at least 1 second interval
  
  //Serial.println("Rover GPS test");

//      if (Serial.available()) {
//        Serial.write(Serial.read());
//      }

}

void pirintLogo(){

  Serial.println(F("************************************************"));
  Serial.println(F("*    Rhea Rover                                *"));
  Serial.println(F("*    SeungMin Shin, Haneulbit Kim, Chan Lee    *"));
  Serial.println(F("*                  powered by Asgardia 2019    *"));  
  Serial.println(F("*      https://github.com/cchamchi/rhea_rover  *"));
  Serial.println(F("************************************************"));

}