
#include "src/rover_gps.h"
#include "src/rover_RoverUltraSonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupRoverGps();

  Serial.println("Rover GPS test");

}

void loop() {
  loopRoverGps(); 
  //loopPassthru();

}
