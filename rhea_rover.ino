<<<<<<< HEAD
  
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"

/* Arduino UNO pin map */
// GPS : 8,9
// BLE : 4,5 (fix)
// Lx16A : 6,7
// SD :  MOSI 11, MISO 12, CLK 13, CS 10
// SHT : SCL,SDA
// MQ7 : A0
// RF & Serial print : 1,2

int joy_velocity=0,joy_raduis=0;

void setup() {

  
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(9600);
  //setupRoverGps();
  //setupRoverAhrs();
   setupRoverMotor();

}

void loop() {
  //loopRoverAhrs();
  //loopRoverGps(); 

  // put your setup code here, to run once:
  
  //setupRoverGps();
  //loopUltraSonicTest();
  RoverMotorTest();
  //Serial.println("dd");
  delay(1000);
  
  //Serial.println("Rover GPS test");

//      if (Serial.available()) {
//        Serial.write(Serial.read());
//      }

}
=======
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"
#include "src/rover_PM2_5.h"

/* software serial pin map */
// GPS : 10,11
// BLE : 4,5
// Lx16A : 6,7

int joy_velocity=0,joy_raduis=0;
int v=0;
void setup() {

  
  //Serial.begin(38400);     //MPU6050 default
  Serial.begin(9600);
  //setupRoverGps();
  //setupRoverAhrs();
  Serial.println("Setup Start!");
  setupRoverMotor();
  Serial.println("Setup Complete!");
  //setupJoystick();
  
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
  void loopRoverPM2_5() //delay 1000 is included in this code
  
  //Serial.println("Rover GPS test");

//      if (Serial.available()) {
//        Serial.write(Serial.read());
//      }

}
>>>>>>> 8b9181ec01ba63975bd3cbd7ca9210c761b3db80
