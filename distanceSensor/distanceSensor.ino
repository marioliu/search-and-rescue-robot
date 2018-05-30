
// sensor in the left
#define trigPinL 6
#define echoPinL 5

// sensor in the right
#define trigPinR 4
#define echoPinR 3

// sensor in the front
#define trigPinF 2
#define echoPinF 1




void setup() {
    Serial.begin (9600);
    
    pinMode(trigPinL, OUTPUT);
    pinMode(echoPinL, INPUT);
  
     pinMode(trigPinR, OUTPUT);
    pinMode(echoPinR, INPUT);
  
     pinMode(trigPinF, OUTPUT);
    pinMode(echoPinF, INPUT);
  
  
  }

void loop() {
  
  long durationL, distanceL, durationR, distanceR, durationF, distanceF;
  
  digitalWrite(trigPinL, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinL, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);
  distanceL = (durationL/2) / 29.1;

    digitalWrite(trigPinR, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinR, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  distanceR = (durationR/2) / 29.1;

    digitalWrite(trigPinF, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinF, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinF, LOW);
  durationF = pulseIn(echoPinF, HIGH);
  distanceF = (durationL/2) / 29.1;

  
  Serial.print("Distance on left sensor: ");
    Serial.println(distanceL);
    Serial.print("Distance on right sensor: ");
    Serial.println(distanceR);
    Serial.println("");


  

//  if (distanceL >= 200 || distanceL <= 0){
//    Serial.println("Left sensor Out of range");
//  }
//  else {
//    Serial.print("Distance on left sensor: ");
//    Serial.print(distanceL);
//    Serial.println(" cm");
//  }
//
//  
//  if (distanceR >= 200 || distanceR <= 0){
//    Serial.println("Right sensor Out of range");
//  }
//  else {
//    Serial.print("Distance on right sensor: ");
//    Serial.print(distanceR);
//    Serial.println(" cm");
//  }

//  
//  if (distanceF >= 200 || distanceF <= 0){
//    Serial.println("Front sensor Out of range");
//  }
//  else {
//    Serial.print("Distance on front sensor: ");
//    Serial.print(distanceF);
//    Serial.println(" cm");
////  }
//  delay(50);
}


