// this function calculates the PID gain based on the errror (discretely)

// this code adapted from: http://blog.solutions-cubed.com/pid-motor-control-with-an-arduino/

int calculatePID(void)
{
  pid = 0;
 
  // Set constants here
  Kp = 60;
  Ki = 20;
  Kd = 20;
  divider = 0.001; // used to scale down the gain

  // Calculate the PID
  accumulator += Error[0];  // accumulator is sum of errors

  // setting the bounds on the max value of the integral of the error
  if (accumulator > 2000)
    accumulator = 2000;
  if (accumulator < -2000)
    accumulator = -2000;

  pid = Error[0] * Kp;   // start with proportional gain
  pid += Ki * accumulator; // add integral gain and error accumulation
  pid += Kd * (Error[0] - Error[8]); // differential gain
  
//  Serial.print("Unscaled PID gains: "); 
//  Serial.println(pid);

  pid = (int)(pid * divider); // scale PID down with divider
  
//     Serial.print("The scaled down PID gain is: ");
//      Serial.println(pid);


  return pid;
}


