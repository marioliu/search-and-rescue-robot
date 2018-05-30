/*
  Testing RC Connection
  4/12/15 by Brian Patton
  Captures the Pulse signal from a RC controller
  Feel free to do whatever you want with this code example
*/
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

// Create Variables to hold the Receiver signals
int Ch1, Ch2, Ch3, Ch4, Ch5, Ch6;
int Lwheel, Rwheel, Bwheel, Aservo;

// Create Servo Objects as defined in the Servo.h files
Servo L_Servo; // Servo DC Motor Driver (Designed for RC cars)
Servo R_Servo; // Servo DC Motor Driver (Designed for RC cars)
Servo B_Servo; // back motors
Servo A_Servo; // arm servo

// setup for the light sensors
const int tolerance = 150; // the tolerance between light values
const long distTolerance = 5.0; // tolerance between dist sensors
long error = 0.0; // error between sensors

const int lightL = A3;  // Analog input pin that the LEFT light pin is connected to
const int lightR = A4; // Analog input pin that the RIGHT light pin is connected to
const int distLight = A5;

int lightValueR; //will track the light sensor values (right)
int lightValueL; //will track the light sensor values (left)
int lightDistance; // to determine if we need to stop

int RightSpeed = 1580; // speed to make it go straight
int LeftSpeed  = 1400; // speed to make it go straight

// booleans for checking run
boolean runWall = true;

//**************************************************************
//*****************  Setup  ************************************
//**************************************************************
void setup() {
  // Set the pins that the transmitter will be connected to all to input
  pinMode(12, INPUT); //I connected this to Chan1 of the Receiver
  pinMode(11, INPUT); //I connected this to Chan2 of the Receiver
  pinMode(10, INPUT); //I connected this to Chan3 of the Receiver
  pinMode(9, INPUT); //I connected this to Chan4 of the Receiver
  pinMode(8, INPUT); //I connected this to Chan5 of the Receiver
  pinMode(7, INPUT); //I connected this to Chan6 of the Receiver
  pinMode(13, OUTPUT); //Onboard LED to output for diagnostics

  // pins for distance sensors
  pinMode(trigPinL, OUTPUT); // left
  pinMode(echoPinL, INPUT); // left
  pinMode(trigPinR, OUTPUT); // right
  pinMode(echoPinR, INPUT); // right
  pinMode(trigPinF, OUTPUT); // front
  pinMode(echoPinF, INPUT); // front

  // Attach controllers that act like servos to the board
  L_Servo.attach(A9);
  R_Servo.attach(A7);
  B_Servo.attach(A2);
  A_Servo.attach(A0);
  
  //Flash the LED on and Off 10x Start
  for (int i = 0; i < 10; i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
  //Flash the LED on and Off 10x End
  Serial.begin(9600);
}

//********************** MixLimits() ***************************
//*******  Make sure values never exceed ranges  ***************
//******  For most all servos and like controlers  *************
//****   control must fall between 1000uS and 2000uS  **********
//**************************************************************
void SetLimits() {
  if (Lwheel < 1000) {// Can be set to a value you don't wish to exceed
    Lwheel = 1000;    // to adjust maximums for your own robot
  }
  if (Lwheel > 2000) {// Can be set to a value you don't wish to exceed
    Lwheel = 2000;    // to adjust maximums for your own robot
  }

  if (Rwheel < 1000) {// Can be set to a value you don't wish to exceed
    Rwheel = 1000;    // to adjust maximums for your own robot
  }
  if (Rwheel > 2000) {// Can be set to a value you don't wish to exceed
    Rwheel = 2000;    // to adjust maximums for your own robot
  }

  if (Bwheel < 1000) {// Can be set to a value you don't wish to exceed
    Bwheel = 1000;    // to adjust maximums for your own robot
  }
  if (Bwheel > 2000) {// Can be set to a value you don't wish to exceed
    Bwheel = 2000;    // to adjust maximums for your own robot
  }

  if (Aservo < 1000) {// Can be set to a value you don't wish to exceed
    Aservo = 1000;    // to adjust maximums for your own robot
  }
  if (Aservo > 2000) {// Can be set to a value you don't wish to exceed
    Aservo = 2000;    // to adjust maximums for your own robot
  }
  L_Servo.writeMicroseconds(Lwheel);
  R_Servo.writeMicroseconds(Rwheel);
  B_Servo.writeMicroseconds(Bwheel);
  A_Servo.writeMicroseconds(Aservo);

  //  PrintWheelCalcs(); //REMEMBER: printing values slows reaction times
}
//*****************  PrintWheelCalcs()  ************************
//*******  Prints calculated wheel output values  **************
//**************************************************************
void PrintWheelCalcs() {
  //Serial.print("Left Wheel = ");
  //Serial.println(Lwheel);
  //Serial.print("Right Wheel = ");
  //Serial.println(Rwheel);
  //Serial.print("Back Wheel = ");
  //Serial.println(Bwheel);
  //Serial.print("Arm Motor = ");
  //Serial.println(Aservo);
  //Serial.println(" ");

}
//********************  TestWheels()  **************************
//*  Direct call to Servos to test wheel speed and direction  **
//**************************************************************
void TestWheels() {
  L_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
  R_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
  B_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
  A_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop

}
//*******************  DriveServosRC()  ************************
//******  Use the value collected from Ch1 and Ch2  ************
//******  on a single stick to relatively calculate  ***********
//****  speed and direction of two servo driven wheels *********
//**************************************************************
void DriveServosRC()
{
  // edge case if remote is off
  if (Ch1 == 0 && Ch2 == 0)
  {
    Lwheel = 1500;
    Rwheel = 1500;
    Bwheel = 1500;
    Aservo = 1500;

    SetLimits();
  }
  else if (Ch2 <= 1500) {
    Lwheel = Ch1 -  Ch2 + 1500;
    Rwheel = Ch1 +  Ch2 - 1500;
    Bwheel = Ch3;
    Aservo = Ch4;

    SetLimits();
  }
  else if (Ch2 > 1500) {
    int Ch1_mod = map(Ch1, 1000, 2000, 2000, 1000); // Invert the Ch1 axis to keep the math similar
    Lwheel = Ch1_mod - Ch2 + 1500;
    Rwheel = Ch1_mod + Ch2 - 1500;
    Bwheel = Ch3;
    Aservo = Ch4;

    SetLimits();
  }
  else {
    Bwheel = Ch3;
    Aservo = Ch4;

    SetLimits();
  }
}
//**********************  PrintRC()  ***************************
//***  Simply print the collected RC values for diagnostics  ***
//**************************************************************
void PrintRC()
{ // print out the values you read in:
  Serial.print("Ch1 = ");
  Serial.println(Ch1);
  Serial.print("Ch2 = ");
  Serial.println(Ch2);
  Serial.print("Ch3 = ");
  Serial.println(Ch3);
  Serial.print("Ch4 = ");
  Serial.println(Ch4);
  Serial.print("Ch5 = ");
  Serial.println(Ch5);
  Serial.print("Ch6 = ");
  Serial.println(Ch6);
  Serial.println(" ");

  PrintWheelCalcs();
}
//**********************  AutoMode() ***************************
//*******************  Autonomous Mode  ************************
//**************************************************************
void AutoMode()
{
  if (runWall) {
    overWall();
    runWall = false;
  }
//  navigateChute();
//  findLight();
//  dropKush();

}
//************************  loop()  ****************************
//**********************  Main Loop  ***************************
//**************************************************************
void loop()
{
  Ch1 = pulseIn(12, HIGH, 21000); // Capture pulse width on Channel 1
  Ch2 = pulseIn(11, HIGH, 21000); // Capture pulse width on Channel 2
  Ch3 = pulseIn(10, HIGH, 21000);  // Capture pulse width on Channel 3, back wheel servo, >1500 forwards
  Ch4 = pulseIn(9, HIGH, 21000);  // Capture pulse width on Channel 4, arm servo
  // clamping ch 4 to slow down arm
  //  Ch4 = map(Ch4, 1000, 2000, 1250, 1750);
  Ch5 = pulseIn(8, HIGH, 21000); // Capture pulse width on Channel 5
  Ch6 = pulseIn(7, HIGH, 21000); // Capture pulse width on Channel 6

  // check if in autonomous mode, right switch in for off, out for on
  if (Ch5 > 1600) {
    Serial.print("*** Auto Mode ***");
    Serial.println(" ");
    AutoMode();
  }
  // if not, manual drive
  else {
    Serial.print("*** RC Mode ***");
    Serial.println(" ");
    //  TestWheels();
    runWall = true;
    DriveServosRC(); // Drive Motors under RC control
    PrintRC(); // Print Values for RC Mode Diagnostics
  }
}
