SoftwareSerial _Mport(6,7);
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

void sendcommand(int v,int r){

  float cornerDeg[4];
  //myRover.getCornerDegree(cornerDeg);

 // Serial.print(cornerDeg[0]);Serial.print(cornerDeg[1]); Serial.print(cornerDeg[2]); Serial.println(cornerDeg[3]); 
 
}
  
