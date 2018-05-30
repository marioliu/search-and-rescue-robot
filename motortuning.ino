#include <Servo.h>

// Creating Servo objwcts

Servo L_Servo;  // Servo DC Motor Driver (Designed for RC cars)

Servo R_Servo;  // Servo DC Motor Driver (Designed for RC cars)

const int tolerance = 150;

int error = 0;



const int lightL = A3;  // Analog input pin that the LEFT light pin is connected to

const int lightR = A4; // Analog input pin that the RIGHT light pin is connected to

const int distLight = A5;

//

int lightValueR; //will track the light sensor values (right)

int lightValueL; //will track the light sensor values (left)

int lightDistance; // to determine if we need to stop

float gain = .85;





void setup() {

  // put your setup code here, to run once:





  // initialize serial communication at 9600 bits per second:

  Serial.begin(9600);



  //Flash the LED on and Off 10x Start

  for (int i = 0; i < 10; i++) {

    digitalWrite(13, HIGH);

    delay(100);

    digitalWrite(13, LOW);

    delay(100);

  }



  // Attach Speed controller that acts like a servo to the board

  L_Servo.attach(3); //Pin 2

  R_Servo.attach(2); //Pin 3



  // initializing the motors, waiting 2 seconds before running the code

  R_Servo.writeMicroseconds(1500);

  L_Servo.writeMicroseconds(1500);

  delay(2000);



}



void loop() {

  // put your main code here, to run repeatedly:

  // initializing the motors, waiting 2 seconds before running the code

  //  R_Servo.writeMicroseconds(1580);

  //  L_Servo.writeMicroseconds(1400);

  //  delay(500);

  //  R_Servo.writeMicroseconds(1500);

  //  L_Servo.writeMicroseconds(1500);

  //  delay(1000);



  lightValueR = analogRead(lightR);

  lightValueL = analogRead(lightL);

  lightDistance = analogRead(distLight);

  error = lightValueR - lightValueL;



  //  // Turns ???

  //  /*

//      Serial.print("Error: ");

//      Serial.println(error);

//      Serial.print("Right Light Sensor: ");

//      Serial.println(lightValueR);

//      Serial.print("Left Light Sensor: ");

//      Serial.println(lightValueL);

//      Serial.print("third sensor");

//      Serial.println(lightDistance);

//      delay(500);

  //    */







//  // Turn right until threshold met

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



  if (lightDistance < 45) {

    while (true) {

           R_Servo.writeMicroseconds(1500);

          L_Servo.writeMicroseconds(1500);

      // Stop forever and ever

    }

  }



  //  // Swivel RIGHT

  if (error < -tolerance) {

    R_Servo.writeMicroseconds(1320);

    L_Servo.writeMicroseconds(1360);

    delay(10);

    R_Servo.writeMicroseconds(1500);

    L_Servo.writeMicroseconds(1500);



  }

  //  // Swivel LEFT

  else if (error > tolerance) {



    R_Servo.writeMicroseconds(1570);

    L_Servo.writeMicroseconds(1570);

    delay(10);

    R_Servo.writeMicroseconds(1500);

    L_Servo.writeMicroseconds(1500);

  }

  // Drive forward

  else {

    while ( abs(error) < tolerance) {

      if (lightDistance < 55) {

        while (true) {

          R_Servo.writeMicroseconds(1500);

          L_Servo.writeMicroseconds(1500);

          // Stop forever and ever

        }

      }



      R_Servo.writeMicroseconds(1580);

      L_Servo.writeMicroseconds(1400);

      lightValueR = analogRead(lightR);

      lightValueL = analogRead(lightL);

      lightDistance = analogRead(distLight);

      error = lightValueR - lightValueL;



      delay(50);

    }

  }



}
