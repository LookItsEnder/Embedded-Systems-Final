#include <Servo.h> // The servo library


Servo servoX; //X rotation Servo
Servo servoY; //Y rotation Servo
const int X_pin = 0; // This pin is for analog controls of the X servo
const int Y_pin = 1; // This pin is for analog controls of the Y servo

int checkRotation(int pos){ // Used for rotation of servo :)
  int reading = analogRead(X_pin);
  int degree = servoX.read();

  if(reading <= 494){ // the reading is to the left 
    pos -= 5; // Turns the servo to the left
  }
  if(reading >= 530){ // the reading is to the right
    pos += 5; // Turns the servo to the right
  }
  if(degree == 0){
    for(int i = 0; i < 5; i++){
      servoX.write(i);
      
    }
  }
  
  return pos;
}


void setup() {
  // put your setup code here, to run once:
  // Servos :)
  servoX.attach(9); // Pin for Signal input on the X servo
  servoY.attach(8); // Pin for Signal input on the Y servo
  Serial.begin(9600); // setup for the serial
}

void loop() {
  // put your main code here, to run repeatedly:
  int xpos;


  xpos = checkRotation(xpos);
  Serial.println(servoX.read()); // used to see what the position is on the servo
  Serial.println(xpos);
  servoX.write(xpos);
  
  delay(20); // Low delay for near instant movement from the servo
}
