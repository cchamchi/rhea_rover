/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/
#include <arduino.h>
#include "rover_motor.h"

#define R_MIN 20.0 //inch
#define R_MAX 250.0

#define V_MIN -100
#define V_MAX 100

RoverMotor::RoverMotor(){

    float currunt_radius=0;

    memset( corner_degree, 0, sizeof(corner_degree));
    memset( velocity_wheel, 0, sizeof(velocity_wheel));

}


void RoverMotor::getCornerDegree(float *corner_degree){
    //get degree of each corner

}
float RoverMotor::approxTurningRadius(float *corner_degree){
    //calculate a approxmate radius of rover using coner's degree
    //Takes the list of current corner angles and approximates the current turning radius [inches]
    //param list [int] enc: List of encoder ticks for each corner motor  
		// if enc[0] == None:
		// 	return 250
		// try:
		// 	if enc[0] > 0:
		// 		r1 = (self.d1/math.tan(math.radians(abs(enc[0])))) + self.d3
		// 		r2 = (self.d2/math.tan(math.radians(abs(enc[1])))) + self.d3
		// 		r3 = (self.d2/math.tan(math.radians(abs(enc[2])))) - self.d3
		// 		r4 = (self.d1/math.tan(math.radians(abs(enc[3])))) - self.d3
		// 	else:
		// 		r1 = -(self.d1/math.tan(math.radians(abs(enc[0])))) - self.d3
		// 		r2 = -(self.d2/math.tan(math.radians(abs(enc[1])))) - self.d3
		// 		r3 = -(self.d2/math.tan(math.radians(abs(enc[2])))) + self.d3
		// 		r4 = -(self.d1/math.tan(math.radians(abs(enc[3])))) + self.d3
		// 	radius = (r1 + r2 + r3 + r4)/4
		// 	return radius
		// except:
		// 	return 250
}
void RoverMotor::calculateVelocity(int vel_joy,float radius,float *velocity_wheel){

		// Returns a list of speeds for each individual drive motor based on current turning radius
		// :param int v: Drive speed command range from -100 to 100
		// :param int r: Turning radius command range from -100 to 100
		// '''

  // transform rover value (-100~100) to real rover veloc,angle
	float velco_rover=map(vel_joy,-100,100,V_MIN,V_MAX); 
	float radius_rover=map(abs(radius),0,100,R_MAX,R_MIN);

  //Drive speed command velco_rover range from V_MIN to V_MAX

	if ( (radius == 0) || (radius>= 250) || ( radius <= -250)){
    	for(int i=0;i<6;i++) velocity_wheel[i]= vel_joy; //all wheels same speed
  	}else{
      // TO-DO : calculate velocity of each wheel
      
      float x = velco_rover/((abs(radius_rover) + d4));                 
      float a = pow(d2,2);
      float b = pow(d3,2);
      float c = pow((abs(radius_rover)+d1),2);
      float d = pow((abs(radius_rover)-d1),2);
      float e = abs(radius)-d4;

      float v1 = x*sqrt(b + c);
      float v2 = velco_rover;       // Fastest wheel
      float v3 = x*sqrt(a + c);
      float v4 = x*sqrt(b + d);
      float v5 = x*e;           // Slowest wheel      
      float v6 = x*sqrt(a + d);

      
      if (radius > 0){
        velocity_wheel[0]=v1; velocity_wheel[1]=v2; velocity_wheel[2]=v3;
        velocity_wheel[3]=v4; velocity_wheel[4]=v5; velocity_wheel[5]=v6;
      }
      else if (radius < 0){
        velocity_wheel[0]=v4; velocity_wheel[1]=v5; velocity_wheel[2]=v6;
        velocity_wheel[3]=v1; velocity_wheel[4]=v2; velocity_wheel[5]=v3;
      }
      
  }
}
void RoverMotor::sendCommand(float *velocity_wheel,float *corner_degree){

}
void RoverMotor::calculateTargetDeg(int radius_joy,float *wh_angle ){

		// '''
		// Takes a turning radius and calculates what angle [degrees] each corner should be at
		// :param int radius: Radius drive command, ranges from -100 (turning left) to 100 (turning right)
		// '''


 	//Radius drive command,r_rover  ranges from -100 (turning left) to 100 (turning right)

  	//Scaled from 250(R_MAX) to 20(R_MIN) inches.

  	float r;

  if(radius_joy == 0) r=R_MAX;
  else if (-100 <= radius_joy <= 100) r = map(abs(radius_joy),0,100,R_MAX,R_MIN);
  else r=R_MAX;

  if (r == R_MAX){
    memset (wh_angle, 0, sizeof(wh_angle));
    return;
  }
  // TO-DO : calculate angle of each wheel 
  //   ang1     ang3
  //   ang2     ang4

  int ang1 = int(degrees(atan(d3/(abs(r)+d1))));
  int ang2 = int(degrees(atan(d2/(abs(r)+d1))));
  int ang3 = int(degrees(atan(d3/(abs(r)-d1))));
  int ang4 = int(degrees(atan(d2/(abs(r)-d1))));

  if (radius_joy > 0){
    wh_angle[0]=ang1; wh_angle[1]=-ang2;
    wh_angle[2]=ang3; wh_angle[3]=-ang4;
  }else{
    wh_angle[0]=-ang1; wh_angle[1]=ang2;
    wh_angle[2]=-ang3; wh_angle[3]=ang4;
  }
  

}

void RoverMotor::cornerPosControl(float *target_degree){

}

