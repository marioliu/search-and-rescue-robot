/*
  Testing RC Connection
  4/12/15 by Brian Patton
  Captures the Pulse signal from a RC controller
  Feel free to do whatever you want with this code example
*/
#include <Servo.h>
int Ch4;


Servo B_Servo; //  back motors

// going to use channel 4 for the back motors


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
  pinMode(2, OUTPUT) ; // left pin output
//  
//  // Attach Speed controller that acts like a servo to the board
//  R_Servo.attach(A9); //Pin A9
//  L_Servo.attach(A7); //Pin A7
  B_Servo.attach(A5); //Pin A9
  //Flash the LED on and Off 10x Start
//  for (int i = 0; i < 10; i++) {
//    digitalWrite(13, HIGH);
//    delay(100);
//    digitalWrite(13, LOW);
//    delay(100);
//  }
  //Flash the LED on and Off 10x End
  Serial.begin(9600);
}

//********************** MixLimits() ***************************
//*******  Make sure values never exceed ranges  ***************
//******  For most all servos and like controlers  *************
//****   control must fall between 1000uS and 2000uS  **********
//**************************************************************
//void SetLimits() {
//  if (Lwheel < 1000) {// Can be set to a value you don't wish to exceed
//    Lwheel = 1000;    // to adjust maximums for your own robot
//  }
//  if (Lwheel > 2000) {// Can be set to a value you don't wish to exceed
//    Lwheel = 2000;    // to adjust maximums for your own robot
//  }
//  
//  if (Rwheel < 1000) {// Can be set to a value you don't wish to exceed
//    Rwheel = 1000;    // to adjust maximums for your own robot
//  }
//  if (Rwheel > 2000) {// Can be set to a value you don't wish to exceed
//    Rwheel = 2000;    // to adjust maximums for your own robot
//  }
//  
//    if (Bwheel < 1000) {// Can be set to a value you don't wish to exceed
//    Bwheel = 1000;    // to adjust maximums for your own robot
//  }
//  if (Bwheel > 2000) {// Can be set to a value you don't wish to exceed
//    Bwheel = 2000;    // to adjust maximums for your own robot
//  }
//  R_Servo.writeMicroseconds(Rwheel);
//  L_Servo.writeMicroseconds(Lwheel);
//  L_Servo.writeMicroseconds(Bwheel);
//  
//  //  PrintWheelCalcs(); //REMEMBER: printing values slows reaction times
//}
//*****************  PrintWheelCalcs()  ************************
//*******  Prints calculated wheel output values  **************
//**************************************************************
//void PrintWheelCalcs() {
//  //Serial.print("Right Wheel = ");
//  //Serial.println(Rwheel);
//  //Serial.print("Left Wheel = ");
//  //Serial.println(Lwheel);
//   //Serial.print("Back Wheel = ");
//  //Serial.println(Bwheel);
//  //Serial.println(" ");
//
//}
//********************  TestWheels()  **************************
//*  Direct call to Servos to test wheel speed and direction  **
//**************************************************************
//void TestWheels() {
//  R_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
//  L_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
//  B_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
//  
//}
//*******************  DriveServosRC()  ************************
//******  Use the value collected from Ch1 and Ch2  ************
//******  on a single stick to relatively calculate  ***********
//****  speed and direction of two servo driven wheels *********
//**************************************************************
//void DriveServosRC()
//{
//  //edge case if the remote is off
//  Serial.print("Ch1: ");
//  Serial.println(Ch1);
//  Serial.print("Ch2: ");
//  Serial.println(Ch2);
//  Serial.print("Ch4: ");
//  Serial.println(Ch4);
//  
//  if(Ch1 == 0 && Ch2 == 0)
//  {
//    Lwheel = 1500; 
//    Rwheel = 1500;
//
//    Serial.println("Ch1 & CH2 are zero, sending 1500 to motors");
//    
//    SetLimits();
//  }
//      else if (Ch2 <= 1500) {
//        Lwheel = Ch1 +  Ch2 - 1500;
//        Rwheel = Ch1 -  Ch2 + 1500;
//        Bwheel = Ch4;
////        Serial.println("Should not be here");
//        
//    SetLimits();
//  }
//  else if (Ch2 > 1500) {
//   int Ch1_mod = map(Ch1, 1000, 2000, 2000, 1000); // Invert the Ch1 axis to keep the math similar
//   Lwheel = Ch1_mod + Ch2 - 1500;
//   Rwheel = Ch1_mod - Ch2 + 1500;
//   Bwheel = Ch4;
//   
////   Serial.println("Should not be here"); 
//
//  
// 
//    SetLimits();
//  }
//  else {
//    Serial.println("Should not be here or in Deadzone");
//  }
//}
////**********************  PrintRC()  ***************************
////***  Simply print the collected RC values for diagnostics  ***
////**************************************************************
//void PrintRC()
//{ // print out the values you read in:
//  Serial.println(" RC Control Mode ");
//  Serial.print("Value Ch1 = ");
//  Serial.println(Ch1);
//  Serial.print("Value Ch2 = ");
//  Serial.println(Ch2);
//  //Serial.print("Value Ch3 = ");
//  //Serial.println(Ch3);
//  Serial.print("Value Ch4 = ");
//  Serial.println(Ch4);
//  Serial.print("Control = ");
//  Serial.println(Ch5);
//  //Serial.print("Value Ch6 = ");
//  //Serial.println(Ch6);
//  //Serial.println(" ");
//  //delay(1000);
//
//
//  Serial.print("Right Wheel = ");
//  Serial.println(Rwheel);
//  Serial.print("Left Wheel = ");
//  Serial.println(Lwheel);
//  Serial.print("Back Wheel = ");
//  Serial.println(Bwheel);
//  Serial.println(" ");
//  
//  
//}
//************************  loop()  ****************************
//**********************  Main Loop  ***************************
//**************************************************************
void loop()
{

//    Ch1 = pulseIn(12, HIGH, 21000); // Capture pulse width on Channel 1
//  Ch2 = pulseIn(11, HIGH, 21000); // Capture pulse width on Channel 2
  //      Ch3 = pulseIn(10, HIGH, 21000);  // Capture pulse width on Channel 3
        Ch4 = pulseIn(9, HIGH, 21000);  // Capture pulse width on Channel 4
  Serial.print("Value Ch4 = ");
  Serial.println(Ch4);
        
//  Ch5 = pulseIn(8, HIGH, 21000); // Capture pulse width on Channel 5
//  //      Ch6 = pulseIn(7, HIGH, 21000); // Capture pulse width on Channel 6

  //  TestWheels();
//  DriveServosRC(); // Drive Motors under RC control
//   PrintRC(); //Print Values for RC Mode Diagnostics
    B_Servo.writeMicroseconds(Ch4); // 1000-2000, 1500 should be stop
//    delay(2000);
//    B_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
//    delay(2000);
//    B_Servo.writeMicroseconds(1400); // 1000-2000, 1500 should be stop
//    delay(2000);
//    B_Servo.writeMicroseconds(1500); // 1000-2000, 1500 should be stop
//    delay(2000);
    
    

}
