#include <CmdMessenger.h>  // CmdMessenger

#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_PM2_5.h"
#include "src/rover_SD.h"

/* software serial pin map */
// GPS : 9,10
// BLE : 4,5
// Lx16A : 6,7
// SD : 13,12,11,10
// MQ7 : 
// UltraSonic : 
// PM2.5 : 
// RF communication :

int joy_velocity=0,joy_raduis=0;
int v=0;

CmdMessenger cmdMessenger = CmdMessenger(Serial);
RoverSD roverSd;

void setup() {

  
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(9600);
  //setupRoverGps();
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
  Serial.println("Loop Start");
  RoverMotorTest();
  Serial.println("Loop Passed");
  //Serial.println("dd");
  loopRoverPM2_5(); //delay 1000 is included in this code
  
  //Serial.println("Rover GPS test");

//      if (Serial.available()) {
//        Serial.write(Serial.read());
//      }

}
