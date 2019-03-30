
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
void setup() {
  
  Serial.begin(38400);     //MPU6050 default
  //setupRoverGps();
  setupRoverAhrs();
}

void loop() {
  loopRoverAhrs();
  //loopRoverGps(); 
  //loopPassthru();

}
