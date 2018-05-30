#include <Servo.h>

//////////////////////////////////DEFINING CONSTANTS TO BE USED IN THE CODE/////////////////////

// Creating Servo objwcts
Servo L_Servo;  // Servo DC Motor Driver (Designed for RC cars)
Servo R_Servo;  // Servo DC Motor Driver (Designed for RC cars)

const int lightL = A3;  // Analog input pin that the LEFT light pin is connected to
const int lightR = A4; // Analog input pin that the RIGHT light pin is connected to

int lightValueR; //will track the light sensor values (right)
int lightValueL; //will track the light sensor values (left)
int desiredError = 0; // want desired error to be 0

// values used in the PID controller
int error;
int Kp, Ki, Kd;
float divider;
int accumulator, pid;
int pidGain;
int PWMOutput;
int difference = 0 ; // difference betwen the light sensors
int refError = 0; //tracking a reference 0
int Error[9]; // declaring an error array that will keep track of the past 9 errors
int errThresh = 100;
int counter;


// defining the global constants for light readings
int max_light = 10; // the value it reads when it gets the max light
int min_light = 911; // the value it reads when it gets the min light


// Create Variables to hold the Receiver signals
int Ch1, Ch2, Ch3, Ch4, Ch5, Ch6;
int CalcHold;        //Variable to temp hold calculations for steering stick corections

// will be used to hold the PWMs sent to motors
int Rwheel;
int Lwheel;

///////////////////////////////////////////////////////////////////////////////////////////////////////////




// the setup routine runs once when you press reset:
void setup() {

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




// the loop routine runs over and over again forever:
void loop() {

  //setting shit to 0
  error = 0;
  lightValueR = 0;
  lightValueR = 0;
  counter = 0;

// <<<<<<< HEAD
//      R_Servo.writeMicroseconds(1700);
//    L_Servo.writeMicroseconds(1300);
//    delay(500);
//=======
//      R_Servo.writeMicroseconds(1650);
//    L_Servo.writeMicroseconds(1350);
//    delay(2000);
//>>>>>>> 8a08a0b36f3cf09eb9da8579024fb7a8adadd2bb
//    R_Servo.writeMicroseconds(1500);
//    L_Servo.writeMicroseconds(1500);
//    delay(2000);

//<<<<<<< HEAD
//
//=======

//>>>>>>> 8a08a0b36f3cf09eb9da8579024fb7a8adadd2bb
    //taking 10 measurements, averaging them
    measureLight();
  
    // calculate the error between the sensors
    int error = (int)getError();
  
//    Serial.print("Error: ");
//    Serial.println(error);
  
    // calculating the PID gains only if error is greater than the threshhold
    if (abs(error) > errThresh) {
      pidGain = calculatePID();
      //
    }
    //  THIS IS REDUNDANT, BUT LEFT HERE FOR NOW
    //  explicitly setting the PID gain to 0 if within error threshold margin 
    else if (abs(error) < errThresh)
    {
//      Serial.println("The error is too small. Not calculating PID gains");
      pidGain = 0;
  
    }
  // calculating and sending the PWM to drive the motors based on the PID gain
    PWMOutput = driveMotors(pidGain);
    Serial.print("The PWM Sent is: ");
    Serial.println(PWMOutput);
    Serial.println("");
    
//<<<<<<< HEAD
    delay(50);
//=======
    delay(100);
//>>>>>>> 8a08a0b36f3cf09eb9da8579024fb7a8adadd2bb

}



