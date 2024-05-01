#include <Servo.h> // Servo Library

// Initialize motor pins!
const int motorX1 = 6;
const int motorX2 = 5;
const int motorY1 = 4;
const int motorY2 = 3;

Servo penServ; // Servo to control the marker
const int X_pin = 0; // X axis of joytick module
const int Y_pin = 1; // Y axis of joytick module
const int sw_pin = 2; // Button on the joystick module

bool elevated; // Controls the elevation of the pen arm.

void penElevation(){ // Interrupt Service Routine to control the elevation of the pen
  if(elevated){ // Lowers the pen Arm
    for(int i = 180; i >= 90; i--){
      penServ.write(i);
    }
    elevated = false;
  }
  else{ //Arm is already lowered, needs to be raised
    for(int i = 90; i <= 180; i++){
      penServ.write(i);
    }
    elevated = true;
  }
}

void setup() {
  // put your setup code here, to run once:
  /* 
   *  L298N module needs both motor inputs at high 
   *  in order for the motor to stop.
   */ 
  pinMode(motorX1, OUTPUT);
  pinMode(motorX2, OUTPUT);
  pinMode(motorY1, OUTPUT);
  pinMode(motorY2, OUTPUT);

  // Attach an ISR to the switch input so we can raise and lower the arm with ease
  pinMode(2, INPUT_PULLUP);
  elevated = true; // Pen arm should automatically be elevated
  attachInterrupt(digitalPinToInterrupt(sw_pin), penElevation, CHANGE);

  Serial.begin(9600); // Serial because I may need to print values in case I am confused
  penServ.attach(9); // Pin for signal input on servo for pencil
  penServ.write(100); // Subject to change, but this line will set the initial position of the servo
}

void loop() {
  // put your main code here, to run repeatedly:   
  int x_reading = analogRead(X_pin); // Reads the position of the joystick along its X axis
  int y_reading = analogRead(Y_pin); // Reads the position of the joystick along its Y axis
  Serial.println(y_reading); //Temp to print values in case I need it

  // Check X readings
  if(x_reading <= 553 && x_reading >= 513){ // Reading is in the dead zone, do not move motor.
    digitalWrite(motorX1, HIGH);
    digitalWrite(motorX2, HIGH);
  }
  if(x_reading > 553){ // Reading is high, move motor one way
    digitalWrite(motorX1, HIGH);
    digitalWrite(motorX2, LOW);
  }
  if(x_reading < 513){ // Reading is low, move motor other way
    digitalWrite(motorX1, LOW);
    digitalWrite(motorX2, HIGH);
  }

  // Check Y readings
  if(y_reading <= 553 && y_reading >= 513){ // Reading is in the dead zone, do not move motor.
    digitalWrite(motorY1, HIGH);
    digitalWrite(motorY2, HIGH);
  }
  if(y_reading > 553){ // Reading is high, move motor one way
    digitalWrite(motorY1, HIGH);
    digitalWrite(motorY2, LOW);
  }
  if(y_reading < 513){ // Reading is low, move motor other way
    digitalWrite(motorY1, LOW);
    digitalWrite(motorY2, HIGH);
  }
  
}