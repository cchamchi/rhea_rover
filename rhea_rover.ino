  
#include "src/rover_gps.h"
#include "src/rover_ultrasonic.h"
#include "src/rover_dht.h"
#include "src/rover_ahrs.h"
void setup() {
<<<<<<< HEAD
  
  Serial.begin(38400);     //MPU6050 default
  //setupRoverGps();
  setupRoverAhrs();
}

void loop() {
  loopRoverAhrs();
  //loopRoverGps(); 
=======
  // put your setup code here, to run once:
  Serial.begin(9600);
  //setupRoverGps();

  Serial.println("Rover GPS test");

}

void loop() {
 //loopRoverGps(); 
>>>>>>> 4b313896c551b5a75984c1dfbd2c01ad00bae6e4
  //loopPassthru();
  loopUltraSonic();
  //loopUltraSonicTest();
}
