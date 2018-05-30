// function to drive the motors
int driveMotors(int pidGain)
{

  // setting the bounds
  if (pidGain >= 500)
    pidGain = 500;
  if (pidGain <= -499)
    pidGain = -499;

//   don't drive the motors if the gain is 0)
  if (pidGain == 0)
  {
    
    L_Servo.writeMicroseconds(1673);
    L_Servo.writeMicroseconds(1350);
    delay(300);
    R_Servo.writeMicroseconds(1500);
    L_Servo.writeMicroseconds(1500);
    delay(100);
  }

  // finding the PWM output
  PWMOutput = pidGain + 1500; 


  if (PWMOutput > 1500) {

    // needs to be flipped to LEFT to make it go forward (left needs >1500 to go forward)
    L_Servo.writeMicroseconds(PWMOutput);
  }

  // needs to be flipped to RIGHT to make it go forward (right needs >1500 to go forward)
  else if (PWMOutput < 1500) {
    R_Servo.writeMicroseconds(PWMOutput);

  }
  else {
    L_Servo.writeMicroseconds(1500);
    R_Servo.writeMicroseconds(1500);
    delay(100);


  }
  return PWMOutput;
}

// functions to make both the wheels move, instead of just one


