#define J_MIN 0
#define J_MAX 100
#define J_STEP 25
SoftwareSerial bleJoystick(5,6);

//https://kocoafab.cc/tutorial/view/532

void setupJoystick(){
  bleJoystick.begin(9600);
  
}

void loopJoystick(){

  if(bleJoystick.available()){
    char data= bleJoystick.read();
    switch(data){
      case 'A':  //ON

        break;

      case 'B':  //OFF
        break;
      case 'C':  // C~K left/right
        joy_raduis=-J_MAX;
        break;
      case 'D':
        joy_raduis=-(J_MIN+3*J_STEP);
        break;
      case 'E':
        joy_raduis=-(J_MIN+2*J_STEP);
        break;
      case 'F':
        joy_raduis=-(J_MIN+J_STEP);
        break;
      case 'G':
        joy_raduis=J_MIN;
        break;
      case 'H':
        joy_raduis=(J_MIN+J_STEP);
        break;
      case 'I':
        joy_raduis=(J_MIN+2*J_STEP);
        break;
      case 'J':
        joy_raduis=(J_MIN+3*J_STEP);
        break;
      case 'k':
        joy_raduis=J_MAX;
        break;

      case 'L':  // L~T foward/backward
        joy_velocity=-J_MAX;
        break;
      case 'M':
        joy_velocity=-(J_MIN+3*J_STEP);
        break;
      case 'N':
        joy_velocity=-(J_MIN+2*J_STEP);
        break;
      case 'O':
        joy_velocity=-(J_MIN+J_STEP);
        break;
      case 'P':
        joy_velocity=J_MIN;
        break;
      case 'Q':
        joy_velocity=(J_MIN+J_STEP);
        break;
      case 'R':
        joy_velocity=(J_MIN+2*J_STEP);
        break;
      case 'S':
        joy_velocity=(J_MIN+3*J_STEP);
        break;
      case 'T':
        joy_velocity=J_MAX;
        break;

                      
    }//end switch case

    // send velocity and radius to Lx16A
    sendcommand(joy_velocity,joy_raduis);
  }
  
}
