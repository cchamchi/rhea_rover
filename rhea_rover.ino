
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupRoverGps();

  Serial.println("Rover GPS test");

}

void loop() {
  loopRoverGps(); 
  //loopPassthru();

}
