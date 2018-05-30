
// this function calculates the error (difference) in the light sensor values

long getError(void) {
  difference = 0;
  byte i = 0; // to be used later on as a counter

 
  difference = lightValueR - lightValueL;
  Serial.print("Difference between the sensors: "); 
  Serial.println(difference); 
  
  // shift error values
  for(i=9;i>0;i--)
    Error[i] = Error[i-1];

  if(abs(difference) > errThresh) {
  // load new error into top array spot  
  Error[0] = desiredError-difference;
  }
  else Error[0] = difference; 

 return Error[0];
}

  

