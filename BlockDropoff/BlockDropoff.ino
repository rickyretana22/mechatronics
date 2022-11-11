#include <AccelStepper.h>

#define diraPin 37
#define stepaPin 12
#define motorInterfaceType 1
#define dirtPin 36
#define steptPin 5

#define dir1 7
#define dir2 8
#define pwm1 9
#define pwm2 10
#define en1 2
#define en2 4
#define enaPin 53
#define entPin 51



AccelStepper steppera = AccelStepper(motorInterfaceType, stepaPin, diraPin);
AccelStepper steppert = AccelStepper(motorInterfaceType, steptPin, dirtPin);
void setup() {
  // put your setup code here, to run once:
  steppera.setMaxSpeed(500);
  steppera.setAcceleration(250);
  steppert.setMaxSpeed(2500);
  steppert.setAcceleration(2500);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(entPin,OUTPUT);
  pinMode(enaPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(entPin,0);
  digitalWrite(enaPin,0);

  delay(1000);

  steppera.moveTo(-2500);
  steppera.runToPosition();
  
  delay(1000);

  steppert.moveTo(5600);
  steppert.runToPosition();

  delay(1000);

  steppera.moveTo(-2700);
  steppera.runToPosition();

  delay(1000);

  steppera.moveTo(-1600);
  steppera.runToPosition();

  delay(1000);

  steppert.moveTo(0);
  steppert.runToPosition();

  delay(1000);

  steppera.moveTo(0);
  steppera.runToPosition();

  delay(1000);
  digitalWrite(entPin,1);
  digitalWrite(enaPin,1);
  
  delay(100000);
}
