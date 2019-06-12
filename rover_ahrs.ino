
#include "src/rover_ahrs.h"

RoverAhrs roverAhrs;

void setupRoverAhrs() {
    Serial.println(F("Start MPU6050"));    
    roverAhrs.begin();
}

void updateRoverAhrs() {
    roverAhrs.update(COMP_FILTER);

}
