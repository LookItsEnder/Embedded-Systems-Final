#include <Servo.h> // The servo library


Servo servoX; //X rotation Servo
const int X_pin = 0; // This pin is for analog controls of the X servo
const int Y_pin = 1; // This pin is for analog controls of the Y servo

int checkRotation(int pos){ // Used for rotation of servo :)
  int reading = analogRead(X_pin);

  if(reading >= 0 && reading <= 494){ // the reading is to the left 
    pos -= 20; // Turns the servo to the left
  }
  if(reading >= 530 && reading <= 1024){ // the reading is to the right
    pos += 20; // Turns the servo to the right
  }
  return pos;
}


void setup() {
  // put your setup code here, to run once:
  // Servos :)
  servoX.attach(9); // Pin for Signal input on the X servo
  Serial.begin(9600); // setup for the serial
}

void loop() {
  // put your main code here, to run repeatedly:
  int xpos;

  if(xpos > 2368){ // rollover for turning right
    while(xpos >= 760){
      xpos -= 20;
    }
  }
  if(xpos < 760){ // rollover for turning left (Not fully functional)
    while(xpos <= 2368){
      xpos += 20;
    }
  }

  xpos = checkRotation(xpos);
  Serial.println(xpos); // used to see what the position is on the servo
  servoX.write(xpos);
  
  delay(20); // Low delay for near instant movement from the servo
}
