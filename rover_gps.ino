SoftwareSerial _GPSport(8,9);

RoverGPS<SoftwareSerial> roverGPS(_GPSport);

void setupRoverGps(){

  // Causion!! When using a Software serial, 
  // must use 9600 baud rate, cause a Software read speed is too late
  Serial.println(F("Start GPS at SoftwareSerial 8,9 "));
  roverGPS.begin(9600);
}

void loopRoverGps(){

  // if(roverGPS.read()){  
  //      Serial.print("date=");
  //      Serial.println(roverGPS.date());
  //      Serial.print("time=");
  //      Serial.println(roverGPS.time()/100.);
  //      Serial.print("lat=");
  //      Serial.println((roverGPS.location().lat* 1.0e-7f),7);
  //      Serial.print("lon=");
  //      Serial.println((roverGPS.location().lng* 1.0e-7f),7);       
  //      Serial.print("altitude(m)=");
  //      Serial.println(roverGPS.location().alt/100.); 
  //      Serial.print("num_sat=");
  //      Serial.println(roverGPS.num_sats()); 
  //      Serial.print("speed(km/s)=");
  //      Serial.println(roverGPS.ground_speed_km());
  //      Serial.print("cource=");
  //      Serial.println(roverGPS.ground_course());
  //      Serial.println("*********************************"); 
  // }   
       
}


void loopPassthru(){
   while (roverGPS.available()) Serial.write(roverGPS.readRaw());
}