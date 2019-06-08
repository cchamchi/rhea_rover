rover_PM2_5 mypm(A0);
float dustDensity;

void loopRoverPM2_5(){
  mypm.calulatePM2_5(dustDensity);
  
  if(dustDensity<0){
    Serial.println("Waiting...");
  }
  if(dustDensity<30){
    Serial.println("What a NICE Air!");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }
  else if(dustDensity<80){
    Serial.println("It's GOOD.");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }
  else if(dustDensity<150){
    Serial.println("It's pretty BAD. Please keep your child from going out.");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }
  else{
    Serial.println("DO NEVER GO OUT!");
    Serial.print("Density: ");
    Serial.print(dustDensity);
    Serial.println("μm/m^3");
  }  
//delay(1000);
}
