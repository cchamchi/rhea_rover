

RoverSHT3x roverSHT3x(0x45);

void setupSHT3x(){
  roverSHT3x.begin();
}

void updateSHT3x(){

  if(roverSHT3x.get()==0){
    Serial.print("Temperature in Celsius : ");
    Serial.println(roverSHT3x.cTemp);
    Serial.print("Temperature in Fahrenheit : ");
    Serial.println(roverSHT3x.fTemp);
    Serial.print("Relative Humidity : ");
    Serial.println(roverSHT3x.humidity);
    Serial.println();
  }



}