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



int photoPin = A2;
int vals[3];                 // array to store three color reading
int delaytime = 80;          // delay between readings to allow phototransistor to come to steady state
char serialByte = '0';        // incoming serial byte to read desired driving mode
int hallPin = A3;
int hallMem = 0;
int hallVal = 0;
float cR=0;
float cG=0;
float cB=0;
int block=0;

const int bluePin = 28;
const int greenPin = 26;
const int redPin = 24;
const int blockDet = 25;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for a serial port connection before continuing.
  }

  steppera.setMaxSpeed(200);
  steppera.setAcceleration(150);
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
  pinMode(bluePin, OUTPUT);  digitalWrite(bluePin, HIGH);
  pinMode(greenPin, OUTPUT); digitalWrite(greenPin, HIGH);
  pinMode(redPin, OUTPUT);   digitalWrite(redPin, HIGH);
  pinMode(A3, INPUT);
}
//_______________________________________________________________________________

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
    //*** set LED color to blue ***/
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, HIGH);

    delay(delaytime);// wait for photo tranistor to come to steady state

    vals[0] = analogRead(photoPin); // read phototransistor and store value
    //Serial.print(vals[0]); Serial.print(", "); // print stored value.

    //*** set LED color to green ***//
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);

    delay(delaytime);// wait for photo tranistor to come to steady state

    vals[1] = analogRead(photoPin); // read phototransistor and store value
    //Serial.print(vals[1]); Serial.print(", "); // print stored value.

    //*** set LED color to Red ***//
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);

    delay(delaytime);// wait for photo tranistor to come to steady state

    vals[2] = analogRead(photoPin); // read phototransistor and store value
    //Serial.println(vals[2]); // print stored value. 
    cR=vals[2];
    cG=vals[1];
    cB=vals[0];

  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH);
  delay(200);

  hallVal=analogRead(A3);
  if (hallVal >=517 || hallVal <=504){
    Serial.println("MAGNET BLOCK");
    Serial.println(hallVal);
    hallMem=1;
    block=0;
  }
  else{
    if (cB>20 && cB<50 && cR>8 && cR<40 && cG>15 && cG<80){
    Serial.println("Blue Block Detected");
    block=0;
    }
    else if(cR > 50){
    Serial.println("Red Block Detected");
    block=1;
    }
    else if(cG > 60 && cG< 30){
    Serial.println("Green Block Detected");
    block=0;
    }
    else{
    Serial.println("No Block");
    block=0;
    }
  }

  if(block==1){
  digitalWrite(entPin,0);
  digitalWrite(enaPin,0);
  steppert.moveTo(5000);
  steppert.runToPosition();

  delay(1000);

  steppera.moveTo(800);
  steppera.runToPosition();
  
  delay(1000);

  steppert.moveTo(2000);
  steppert.runToPosition();

  delay(1000);

  steppera.moveTo(0);
  steppera.runToPosition();

  delay(1000);

  steppert.moveTo(0);
  steppert.runToPosition();

  delay(1000);
  digitalWrite(entPin,1);
  digitalWrite(enaPin,1);
  delay(10);
  block=0;
  cR=5;
  cB=5;
  cG=5;
  hallVal=510;
  }
}
