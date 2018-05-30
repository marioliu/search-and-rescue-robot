
// This function measures the light sensor values

void measureLight() 
{

//taking 20 measurements, averaging them
  for (int i = 0; i < 5; i++)
  {   lightValueL += analogRead(lightL);  // reading in the left sensor
      lightValueR += analogRead(lightR);  // reading in the right sensor
      counter = counter + 1;
  }
   lightValueL = lightValueL / counter; // finding the light sensor measurement
   lightValueR = lightValueR / counter; 

     //mapping the values to a new scale (outputs max number if it gets the brightest light, and vice versa)
  lightValueL = map(lightValueL, min_light, max_light, 10, 911);
  lightValueR = map(lightValueR, min_light, max_light, 10, 911);

  Serial.print("Left sensor value: "); 
   Serial.println(lightValueL);
   Serial.print("Right sensor value: "); 
   Serial.println(lightValueR);
//   Serial.println("");
//   
   

}

