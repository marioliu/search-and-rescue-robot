void overWall() {
  Serial.print("overWall()");
  Serial.println(" ");

  int LeftSpeed  = 1350; // 1380
  int RightSpeed = 1730; // 1680
  int BackSpeed = 1650; // 1650

  L_Servo.writeMicroseconds(LeftSpeed);
  R_Servo.writeMicroseconds(RightSpeed);
  B_Servo.writeMicroseconds(BackSpeed);

  for (int i = 0; i < 80; i++) {
    // switch back to RC mode
    if (Ch5 < 1600) return;
    delay(100);
  }

  L_Servo.writeMicroseconds(1500);
  R_Servo.writeMicroseconds(1500);
  B_Servo.writeMicroseconds(1500);
  
} 
