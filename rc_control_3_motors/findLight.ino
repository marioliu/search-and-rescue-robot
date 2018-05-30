void findLight() {
  Serial.print("findLight()");
  Serial.println(" ");
  
  lightValueR = analogRead(lightR); // reading right value
  lightValueL = analogRead(lightL); // reading left value
  lightDistance = analogRead(distLight);
  error = lightValueR - lightValueL; // finding the error between light values

  while (true) {
    while (lightValueR > 650 && lightValueL > 650) {
      R_Servo.writeMicroseconds(1375);
      L_Servo.writeMicroseconds(1400);
      
      delay(100);

      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);

      lightValueR = analogRead(lightR);
      lightValueL = analogRead(lightL);
      lightDistance = analogRead(distLight);
    }

    // returns when close to basket
    if (lightDistance < 100) {
      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);
      return;
    }

    // turn RIGHT
    if (error < -tolerance) {
//      RightSpeed = RightSpeed + 15;
//      LeftSpeed = LeftSpeed - 10;
      R_Servo.writeMicroseconds(1320);
      L_Servo.writeMicroseconds(1360);
      //    R_Servo.writeMicroseconds(RightSpeed);
      //    L_Servo.writeMicroseconds(LeftSpeed);

      delay(10);

      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);
    }

    // turn LEFT
    else if (error > tolerance) {
//      LeftSpeed = LeftSpeed - 10;

      //    R_Servo.writeMicroseconds(RightSpeed);
      //    L_Servo.writeMicroseconds(LeftSpeed);
      R_Servo.writeMicroseconds(1570);
      L_Servo.writeMicroseconds(1570);

      delay(10);

      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);

    }

    // Drive forward
    else {
      while (abs(error) < tolerance) {
        if (lightDistance < 100) {
          R_Servo.writeMicroseconds(1500);
          L_Servo.writeMicroseconds(1500);
          return;
        }

        R_Servo.writeMicroseconds(RightSpeed);
        L_Servo.writeMicroseconds(LeftSpeed);

        lightValueR = analogRead(lightR);
        lightValueL = analogRead(lightL);
        lightDistance = analogRead(distLight);
        error = lightValueR - lightValueL;
        
        delay(50);
      }
    }
  }
}

