#include <Servo.h>

Servo servoPump;
Servo servoScroll;
                
int angle = 0;
int movement = 0;
int min = 1;
int max = 4;

boolean pressed = false;

int pressSensor = A1;

void setup() 
{ 
  Serial.begin(9600);
  servoPump.attach(9);
  servoScroll.attach(10);
  servoScroll.write(90);
  servoPump.write(map(487, 0, 1023, 0, 180));
  delay(100);

  pressed = false;

  //movement = 1;
  
  //servoScrollControl();
  //delay(2000);
  //servoScrollOriginPosition();
}

int getPressSensorValue() {
  int pressValue = analogRead(pressSensor);
  Serial.print("pressure =  ");
  Serial.println(pressValue);
  delay(200);
  return pressValue;
}

void servoScrollOriginPosition() {
  int delayTime = 1550 * movement;

  Serial.println("scroll to origin");
  Serial.print("move = ");
  Serial.println(movement);
  Serial.println(delayTime);
  
  servoScroll.write(0);
  delay(delayTime);
  servoScroll.write(90);
  delay(10);
}

void servoScrollControl() {
  movement = random(min, max);
  int delayTime = 1550 * movement;

  Serial.println("scroll");
  Serial.print("move = ");
  Serial.println(movement);
  Serial.println(delayTime);
  
  servoScroll.write(180);
  delay(delayTime);
  servoScroll.write(90);
  delay(10);
}

void servoPumpControl() {
    servoPump.write(map(300, 0, 1023, 0, 180));
    delay(1800);
                               
    servoPump.write(map(487, 0, 1023, 0, 180));
    delay(1000);
}

void loop() 
{
  if(getPressSensorValue() > 100) {
      pressed = true;
  } else {
    if(pressed) {
      Serial.println("scroll");
      servoScrollControl();
      servoScroll.write(90);
      delay(100);
      
      servoPumpControl();
      pressed = false;
      Serial.println("pump");
      delay(5000);
      servoScrollOriginPosition();
      delay(1000);
    }
  }
}
