#include <Servo.h> // Servo Library

int motorY1 = 3;
int motorY2 = 4;
Servo penServ; // Servo to control the marker
const int X_pin = 0; // X gantry
const int Y_pin = 1; // Y gantry
const int sw_pin = 2; // To be used for the pencil elevation

bool elevated; // Controls the elevation of the pen arm.

void penElevation(){
  if(elevated){ // Lowers the pen Arm
    for(int i = 180; i >= 90; i--){
      penServ.write(i);
    }
    elevated = false;
  }
  else{ //Arm is already lowered, needs to be raised.
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
  pinMode(motorY1, OUTPUT);
  pinMode(motorY2, OUTPUT);

  // Attach an ISR to the switch input so we can raise and lower the arm with ease
  pinMode(2, INPUT_PULLUP);
  elevated = true; // Pen arm should automatically be elevated.
  attachInterrupt(digitalPinToInterrupt(sw_pin), penElevation, CHANGE);

  Serial.begin(9600);
  penServ.attach(9); // Pin for signal input on servo for pencil
  penServ.write(100);
}

void loop() {
  // put your main code here, to run repeatedly:   
  int y_reading = analogRead(Y_pin);
  Serial.println(y_reading);

  if(y_reading <= 553 && y_reading >= 513){
    digitalWrite(motorY1, HIGH);
    digitalWrite(motorY2, HIGH);
  }
  if(y_reading > 553){
    digitalWrite(motorY1, HIGH);
    digitalWrite(motorY2, LOW);
  }
  if(y_reading < 513){
    digitalWrite(motorY1, LOW);
    digitalWrite(motorY2, HIGH);
  }
  
}