void dropKush() {
  Serial.print("dropKush()");
  Serial.println(" ");
  B_Servo.writeMicroseconds(1500);

  // switch back to RC mode
  if (Ch5 < 1600) return;

  int val = digitalRead(sigPin);
  Serial.print("Button is: ");
  Serial.println(val);

  while (val != HIGH) {
    // switch back to RC mode
    if (Ch5 < 1600) return;
  
    A_Servo.writeMicroseconds(1600);
    val = digitalRead(sigPin);
  }
  
  A_Servo.writeMicroseconds(1500);

  // driving robot backwards
  R_Servo.writeMicroseconds(1680); // right offset by 180
  L_Servo.writeMicroseconds(1380); // left offset by 120

  for (int i = 0; i < 30; i++) {
    // switch back to RC mode
    if (Ch5 < 1600) return;
    delay(100);
  }

  R_Servo.writeMicroseconds(1500);
  L_Servo.writeMicroseconds(1500);
}
