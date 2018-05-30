#include <Servo.h>

// sensor in the left
#define trigPinL 6
#define echoPinL 5

// sensor in the right
#define trigPinR 4
#define echoPinR 3

// sensor in the front
#define trigPinF 2
#define echoPinF 1

Servo L_Servo;  // Servo DC Motor Driver (Designed for RC cars)
Servo R_Servo;  // Servo DC Motor Driver (Designed for RC cars)

long distTolerance;
long error;

void setup() {
  Serial.begin (9600);

  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);

  //     pinMode(trigPinF, OUTPUT);
  //    pinMode(echoPinF, INPUT);

  // Assign pins to servos
  L_Servo.attach(A9);
  R_Servo.attach(A7);

    // set tolerance (cm)
  distTolerance = 5.0;
  error = 0.0;
}

void loop() {

  // speed constants to drive forward in a straight line
  int RightSpeed = 1580; // was 1580
  int LeftSpeed  = 1400;

  long durationL, distanceL, durationR, distanceR, durationF, distanceF;

  digitalWrite(trigPinL, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinL, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = (durationL/2.0) / 29.1;

  digitalWrite(trigPinR, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinR, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = (durationR/2.0) / 29.1;

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




  // If distance is too close or too far stop completely 
  if (distanceL >= 200 || distanceL <= 0){
    Serial.println("Left sensor Out of range");
    R_Servo.writeMicroseconds(1500);
    L_Servo.writeMicroseconds(1500);
  }
  else {
    Serial.print("Distance on left sensor: ");
    Serial.print(distanceL);
    Serial.println(" cm");
  }
//
//
  if (distanceR >= 200 || distanceR <= 0){
    Serial.println("Right sensor Out of range");
    R_Servo.writeMicroseconds(1500);
    L_Servo.writeMicroseconds(1500);
  }
  else {
    Serial.print("Distance on right sensor: ");
    Serial.print(distanceR);
    Serial.println(" cm");
  }
//
  // calculate error between two distance readings
  // Want them to be seperated by specified tolerance
  error = distanceL - distanceR;

  // turn left if more space on left side
  if (error > distTolerance) {
     Serial.println("turning left");
    // LeftSpeed = LeftSpeed - 10;
//    RightSpeed = RightSpeed + 15;
    
//L_Servo.writeMicroseconds(LeftSpeed + 10);
//R_Servo.writeMicroseconds(RightSpeed + 10);

//
    R_Servo.writeMicroseconds(1300);
    L_Servo.writeMicroseconds(1500);
    delay(10);
  
    

  }

  // turn right if more space on right side
  else if (error < -distTolerance) {
     Serial.println("turning right"); 
//    LeftSpeed = LeftSpeed - 10;
//    R_Servo.writeMicroseconds(RightSpeed - 10 );
//    L_Servo.writeMicroseconds(LeftSpeed - 10);
//     R_Servo.writeMicroseconds(1320);
      R_Servo.writeMicroseconds(1500);
     L_Servo.writeMicroseconds(1600);
    delay(10);

  }

  // if within tolerance, continue driving straight
  else {
 
    while ( abs(error) < distTolerance) {
      R_Servo.writeMicroseconds(RightSpeed);
      L_Servo.writeMicroseconds(LeftSpeed);
      delay(50);


   digitalWrite(trigPinL, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinL, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = (durationL/2.0) / 29.1;

  digitalWrite(trigPinR, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinR, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = (durationR/2.0) / 29.1;

  error = distanceL - distanceR;

  
      

   
   Serial.println("in while loop");
   Serial.print("error: ");
   Serial.println(error);
   Serial.print("distanceL ");
   Serial.println(distanceL);
    }
  }
//
//  //  if (distanceF >= 200 || distanceF <= 0){
//  //    Serial.println("Front sensor Out of range");
//  //  }
//  //  else {
//  //    Serial.print("Distance on front sensor: ");
//  //    Serial.print(distanceF);
//  //    Serial.println(" cm");
//  //  }

//   delay(50);
}



