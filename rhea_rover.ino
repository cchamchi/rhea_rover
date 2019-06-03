  
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
#include "src/rover_Lx16A.h"
#include "src/rover_motor.h"


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
