RoverPM2_5 roverPM2_5(A1,3);
float dustDensity;

void setupRoverPM2_5(){
  Serial.println(F("Start PM2.5 sensor at A1,3 "));
  roverPM2_5.begin();
}

void updateRoverPM2_5(){
  dustDensity=roverPM2_5.calulatePM2_5();
  
  // if(dustDensity<0){
  //   Serial.println("Waiting...");
  // }
  // if(dustDensity<30){
  //   Serial.println("What a NICE Air!");
  //   Serial.print("Density: ");
  //   Serial.print(dustDensity);
  //   Serial.println("μm/m^3");
  // }
  // else if(dustDensity<80){
  //   Serial.println("It's GOOD.");
  //   Serial.print("Density: ");
  //   Serial.print(dustDensity);
  //   Serial.println("μm/m^3");
  // }
  // else if(dustDensity<150){
  //   Serial.println("It's pretty BAD. Please keep your child from going out.");
  //   Serial.print("Density: ");
  //   Serial.print(dustDensity);
  //   Serial.println("μm/m^3");
  // }
  // else{
  //   Serial.println("DO NEVER GO OUT!");
  //   Serial.print("Density: ");
  //   Serial.print(dustDensity);
  //   Serial.println("μm/m^3");
  // }  
  // delay(1000);
}
