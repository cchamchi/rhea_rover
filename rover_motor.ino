SoftwareSerial _Mport(5,6);
RoverMotor myRover(_Mport);

void setupRoverMotor(){
  float corner_degree[4];
  myRover.begin(9600);

}

void loopRoverMotor(){
  
}



void RoverMotorTest(){
  float corner_degree[4];
  myRover.getCornerDegree(corner_degree);

}

void sendcommand(float v,float r){

  float cornerDeg[4];
  //myRover.getCornerDegree(cornerDeg);

 // Serial.print(cornerDeg[0]);Serial.print(cornerDeg[1]); Serial.print(cornerDeg[2]); Serial.println(cornerDeg[3]); 
 
}
  
