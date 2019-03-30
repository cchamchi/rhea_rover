<<<<<<< HEAD
  void setupUltraSonic(){
    // pin mode settup
=======
>>>>>>> 4b313896c551b5a75984c1dfbd2c01ad00bae6e4


unsigned long distance_cm;
RoverUltraSonic sonicpin(13,12); // (trig, echo)
void setupUltraSonic(){ 

}
float distance;

void loopUltraSonic(){ 
   //measure the distance
  distance=sonicpin.measureDistance();
  
  sonicpin.isDistanceInArea(20,1);
   //is Distance in Area??

   // Do someting

}

void loopUltraSonicTest(){
  distance=sonicpin.measureDistance();
    // //measure the distance);
  Serial.println(distance);
    // print distance
  delay(500);

}
