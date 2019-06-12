unsigned long distance_cm;
RoverUltraSonic roverUltraSonic(4,5); // (trig, echo)
void setupUltraSonic(){ 
  Serial.println(F("Start UltraSonic sensor at  4 trig,5 echo "));
  roverUltraSonic.begin();
}
float distance;

void updateUltraSonic(){ 
   //measure the distance
  distance=roverUltraSonic.measureDistance();

}

void loopUltraSonicTest(){
  distance=roverUltraSonic.measureDistance();
    // //measure the distance);
  Serial.println(distance);
    // print distance
  delay(500);

}
