void findLight() {
  Serial.print("findLight()");
  Serial.println(" ");
  B_Servo.writeMicroseconds(1500);

  while (true) {
    // switch back to RC mode
    if (Ch5 < 1600) return;

    lightValueR = analogRead(lightR); // reading right value
    lightValueL = analogRead(lightL); // reading left value
    error = lightValueR - lightValueL; // finding the error between light values
    Serial.println("*** SENSOR READINGS ***");
    Serial.print("Left light: ");
    Serial.println(lightValueL);

    Serial.print("Right light: ");
    Serial.println(lightValueR);

    digitalWrite(trigPinB, LOW);  // Added this line
    delayMicroseconds(2); // Added this line
    digitalWrite(trigPinB, HIGH);
    //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPinB, LOW);
    durationB = pulseIn(echoPinB, HIGH);
    distanceB = (durationB / 2) / 29.1;

    Serial.print("Back dist: ");
    Serial.println(distanceB);
    Serial.println();

    // delay and continue used for debugging
    //    delay(500);
    //    continue;

    while (lightValueR > 650 && lightValueL > 650) {
      Serial.println("ALIGNING ITSELF TO LIGHT");

//      Serial.print("Back dist: ");
//    Serial.println(distanceB);
//    Serial.println();

///////
//    digitalWrite(trigPinB, LOW);  // Added this line
//    delayMicroseconds(2); // Added this line
//    digitalWrite(trigPinB, HIGH);
//    //  delayMicroseconds(1000); - Removed this line
//    delayMicroseconds(10); // Added this line
//    digitalWrite(trigPinB, LOW);
//    durationB = pulseIn(echoPinB, HIGH);
//    distanceB = (durationB / 2) / 29.1;
    ///////////////////////////
      R_Servo.writeMicroseconds(1850);
      L_Servo.writeMicroseconds(1850);

      delay(50);

      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);

      lightValueR = analogRead(lightR);
      lightValueL = analogRead(lightL);
    }

    // returns when close to basket
    if (distanceB < 15.0) {
      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);
      return;
    }

    // turn RIGHT
    if (error < -tolerance) {
      Serial.println("TURNING RIGHT");
      //      RightSpeed = RightSpeed + 15;
      //      LeftSpeed = LeftSpeed - 10;
      R_Servo.writeMicroseconds(1300);
      L_Servo.writeMicroseconds(1300);
      //    R_Servo.writeMicroseconds(RightSpeed);
      //    L_Servo.writeMicroseconds(LeftSpeed);
      Serial.print("Turn Right");
      delay(100); //50

      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);
    }

    // turn LEFT
    else if (error > tolerance) {
      Serial.println("TURNING LEFT");
      //      LeftSpeed = LeftSpeed - 10;

      //    R_Servo.writeMicroseconds(RightSpeed);
      //    L_Servo.writeMicroseconds(LeftSpeed);
      R_Servo.writeMicroseconds(1700);
      L_Servo.writeMicroseconds(1700);
      Serial.print("Turn Left");
      delay(100); //50 

      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);

    }

    // Drive forward
    else {
      while ((abs(error) < tolerance) && distanceB > 15) {
        // switch back to RC mode
        if (Ch5 < 1600) return;

        //        if (distanceB < 15.0 && distanceB > 10.0) {
        //          R_Servo.writeMicroseconds(1500);
        //          L_Servo.writeMicroseconds(1500);
        //          return;
        //        } Ignoring for now since I don't know what this does and it works without it-Fred

        Serial.println("DRIVING BACK");
        Serial.print("Left light: ");
        Serial.println(lightValueL);

        Serial.print("Right light: ");
        Serial.println(lightValueR);
        Serial.println("");
        if (distanceB < 60) {
          R_Servo.writeMicroseconds(1375);
        L_Servo.writeMicroseconds(1650);

        }
        else {
        R_Servo.writeMicroseconds(1250);
        L_Servo.writeMicroseconds(1790);
        }

        lightValueR = analogRead(lightR);
        lightValueL = analogRead(lightL);

        // update light distance
        digitalWrite(trigPinB, LOW);  // Added this line
        delayMicroseconds(2); // Added this line
        digitalWrite(trigPinB, HIGH);
        //  delayMicroseconds(1000); - Removed this line
        delayMicroseconds(10); // Added this line
        digitalWrite(trigPinB, LOW);
        durationB = pulseIn(echoPinB, HIGH);
        distanceB = (durationB / 2) / 29.1;

        error = lightValueR - lightValueL;
          delay(150); //50
        
      }
    }
    if (distanceB < 60) {
      tolerance = 300;
    }
  }


}

