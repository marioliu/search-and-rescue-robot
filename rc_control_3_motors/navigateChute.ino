void navigateChute() {
  Serial.print("navigateChute()");
  Serial.println(" ");

  while (true) {
    // speed constants to drive forward in a straight line
    int RightSpeed = 1580; // was 1580
    int LeftSpeed  = 1400;

    long durationL, distanceL, durationR, distanceR, durationF, distanceF;

    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    durationL = pulseIn(echoPinL, HIGH);
    distanceL = (durationL / 2.0) / 29.1;

    digitalWrite(trigPinR, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinR, HIGH);
    //  delayMicroseconds(1000); - Removed this line
    delayMicroseconds(10);
    digitalWrite(trigPinR, LOW);
    durationR = pulseIn(echoPinR, HIGH);
    distanceR = (durationR / 2.0) / 29.1;

    //  Serial.print("Distance on left sensor: ");
    //    Serial.println(distanceL);
    //    Serial.print("Distance on right sensor: ");
    //    Serial.println(distanceR);
    //    Serial.println("");
    //

    //    digitalWrite(trigPinF, LOW);  // Added this line
    //  delayMicroseconds(2); // Added this line
    //  digitalWrite(trigPinF, HIGH);
    ////  delayMicroseconds(1000); - Removed this line
    //  delayMicroseconds(10); // Added this line
    //  digitalWrite(trigPinF, LOW);
    //  durationF = pulseIn(echoPinF, HIGH);
    //  distanceF = (durationF/2) / 29.1;

    // if distance is too close or too far, stop completely
    if (distanceL >= 200 || distanceL <= 0) {
      Serial.println("Left sensor Out of range");
      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);
      return;
    }
    else {
      Serial.print("Distance on left sensor: ");
      Serial.print(distanceL);
      Serial.println(" cm");
    }
    if (distanceR >= 200 || distanceR <= 0) {
      Serial.println("Right sensor Out of range");
      R_Servo.writeMicroseconds(1500);
      L_Servo.writeMicroseconds(1500);
      return;
    }
    else {
      Serial.print("Distance on right sensor: ");
      Serial.print(distanceR);
      Serial.println(" cm");
    }

    // calculate error between two distance readings
    // want them to be separated by specified tolerance
    error = distanceL - distanceR;

    // turn left if more space on left side
    if (error > distTolerance) {
      Serial.println("turning left");

      // move forward a little first
      R_Servo.writeMicroseconds(1710); // 1660 original  // 1710 is faster, but also works!!!
      L_Servo.writeMicroseconds(1350); // 1400 original  // 1350 is faster, but also works!!!
      delay(10);

      R_Servo.writeMicroseconds(1695);
      L_Servo.writeMicroseconds(1430);
      delay(10);
    }

    // turn right if more space on right side
    else if (error < -distTolerance) {
      Serial.println("turning right");

      // move forward a little first
      R_Servo.writeMicroseconds(1710); // 1660 original  // 1710 is faster, but also works!!!
      L_Servo.writeMicroseconds(1350); // 1400 original  // 1350 is faster, but also works!!!
      delay(10);
      
      R_Servo.writeMicroseconds(1600);
      L_Servo.writeMicroseconds(1300);
      delay(10);
    }

    // if within tolerance, continue driving straight
    else {
      while (abs(error) < distTolerance) {
        R_Servo.writeMicroseconds(1680);
        L_Servo.writeMicroseconds(1380);
        delay(100);

        digitalWrite(trigPinL, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPinL, HIGH);
        //  delayMicroseconds(1000); - Removed this line
        delayMicroseconds(10);
        digitalWrite(trigPinL, LOW);
        durationL = pulseIn(echoPinL, HIGH);
        distanceL = (durationL / 2.0) / 29.1;

        digitalWrite(trigPinR, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPinR, HIGH);
        //  delayMicroseconds(1000); - Removed this line
        delayMicroseconds(10);
        digitalWrite(trigPinR, LOW);
        durationR = pulseIn(echoPinR, HIGH);
        distanceR = (durationR / 2.0) / 29.1;

        error = distanceL - distanceR;

        Serial.println("in while loop, within tolerance");
        Serial.print("error: ");
        Serial.println(error);
        Serial.print("distanceL: ");
        Serial.println(distanceL);
      }
    }
  }
}
