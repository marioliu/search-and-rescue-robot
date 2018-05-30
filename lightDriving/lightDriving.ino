#include <Servo.h>

// Creating Servo objwcts
Servo L_Servo;  // Servo DC Motor Driver (Designed for RC cars)
Servo R_Servo;  // Servo DC Motor Driver (Designed for RC cars)

const int lightL = A3;  // Analog input pin that the LEFT light pin is connected to
const int lightR = A4; // Analog input pin that the RIGHT light pin is connected to

// values used for tracking
int difference = 0 ; // difference betwen the light sensors
int refError = 0; // tracking a reference 0
int error = refError - difference; // actual error in the system
int Kp = 1; 
//boolean run = false;

// defining the global constants
int max_light = 10; // the value it reads when it gets the max light
int min_light = 911; // the value it reads when it gets the min light


// writing code that allows us to smooth the light readings
// variables for smoothing the left light
const int numReadingsL = 10;
int lightReadingsL[numReadingsL];
int readIndexL = 0;
int totalL = 0;
int averageL = 0;
// variables for smoothing the right light
const int numReadingsR = 10;
int lightReadingsR[numReadingsR];
int readIndexR = 0;
int totalR = 0;
int averageR = 0;

// Create variables to hold the receiver signals
int Ch1, Ch2, Ch3, Ch4, Ch5, Ch6;
int CalcHold;        //Variable to temp hold calculations for steering stick corections

// will be used to hold the PWMs sent to motors
int Rwheel;
int Lwheel;

// function to drive the motors
void driveMotors(int error)
{
  //need fancy controller here
  int newError = Kp*error;
  int calculatedPWM = map(newError, -911, 911, 1000, 2000); // calculate the PWM required
  if (abs(error) > 100) {
    if(calculatedPWM > 1500) {
      int temp = 1500-calculatedPWM; 
      int temp2 = 1500 + temp;
      
//      Serial.println("Greater than 1500 loop");
//      Serial.print("CalculatedPWM: ");
//      Serial.println(temp2);
      
      R_Servo.writeMicroseconds(temp2);
    }
   
    else if(calculatedPWM < 1500) {
      int temp = 1500-calculatedPWM; 
      int temp2 = 1500 + temp;
    
      L_Servo.writeMicroseconds(temp2);
//      Serial.println("Less than 1500 loop");
//      Serial.print("CalculatedPWM: ");
//      Serial.println(calculatedPWM);
    
    }
  }
  
  else {
//    Serial.println("Error is less than 100");
//      if (run == false)
//    {
//    R_Servo.writeMicroseconds(1400);
//    L_Servo.writeMicroseconds(1600);
//    delay(500);
//    run = true;
//    }
  }
}


// the setup routine runs once when you press reset:
void setup() {
  // Attach Speed controller that acts like a servo to the board
  R_Servo.attach(A7); //Pin A7
  L_Servo.attach(A9); //Pin A9

  //Flash the LED on and Off 10x Start
  for (int i = 0; i < 10; i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize all the readings to 0 —LEFT:
  for (int thisReadingL =0; thisReadingL < numReadingsL; thisReadingL++) {
    lightReadingsL[thisReadingL]=0;
    
  }
  // initialize all the readings to 0 —RIGHT:
  for (int thisReadingR =0; thisReadingR < numReadingsR; thisReadingR++) {
    lightReadingsR[thisReadingR]=0;
    
  }
}


// the loop routine runs over and over again forever:
void loop() {

  //setting shit to 0
error = 0;
int calculatedPWM = 1500; 

  
  // read the input on analog pin 0:
int lightValueL = analogRead(lightL);  // reading in the left sensor
int lightValueR = analogRead(lightR);  // reading in the right sensor

//mapping the values to a new scale
 lightValueL = map(lightValueL, min_light, max_light, 10, 911);
 lightValueR = map(lightValueR, min_light, max_light, 10, 911);



// Smoothing out the data from the sensors sensor

// subtract the last reading-left
totalL = totalL - lightReadingsL[readIndexL];
// subtract the last reading-right
totalR = totalR - lightReadingsR[readIndexR];



// read from the light sensor-left
lightReadingsL[readIndexL] = lightValueL;
// read from the light sensor-right
lightReadingsR[readIndexR] = lightValueR;



// add the reading to the total-left
totalL = totalL + lightReadingsL[readIndexL];
// add the reading to the total-right
totalR = totalR + lightReadingsR[readIndexR];



// advance to the next position in the array-left
readIndexL = readIndexL + 1;
// advance to the next position in the array-right
readIndexR = readIndexR + 1;



// if at the end of the array, wrap to the beginning
if (readIndexL >= numReadingsL) {
  readIndexL = 0;
}

// if at the end of the array, wrap to the beginning
if (readIndexR >= numReadingsR) {
  readIndexR = 0;
}


// calculate the average:
averageL = totalL/numReadingsL;
// calculate the average:
averageR = totalR/numReadingsR;



// will be positive if R > L, which means right side is closer to light
difference = averageR - averageL; 

// will be negative if R>L, which means we want to turn to the right. 
error = -(refError - difference); 



driveMotors(error); 

Serial.print("Left sensors: ");
Serial.println(averageL);
Serial.print("Right sensors: ");
Serial.println(averageR);

Serial.print("Error between sensors: ");
Serial.println(error);
Serial.print("Calculated PWM: ");
Serial.println(calculatedPWM);
Serial.println("");
delay(50);

}



////setup loop that runs once
//void setup() {
//  // initialize serial communication at 9600 bits per second:
//  Serial.begin(9600);
//}



//// the loop routine runs over and over again forever:
//void loop() {
//  
//  //read the input on analog pin 0:
// lightValue = analogRead(lightPin);
//
// 
// driveServos(); 
// 
//  
//  printData(); 
//  
//  delay(50); 
//
//}
//
//  //this function will calculate the PWMs based on the light source
// void calculatePWMs() {
//  
//
//
// }
//
// void driveServos() {
//
//
//
//  
// }
// 
//
//// this is a debugging function that will print the data being used
//void printData()
//{
//  Serial.print("Light Sensor Value: ");
//  Serial.println(lightValue);
//  Serial.println("");
//  
//  
//}

