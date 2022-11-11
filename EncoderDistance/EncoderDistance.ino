#include "Encoder.h"
#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield md; 

#define dir1 7
#define dir2 8
#define pwm1 9
#define pwm2 10
#define en1 2
#define en2 4

Encoder myEnc1(18,19);
Encoder myEnc2(20,21);


//time variables
unsigned long tm = 0;              //current time
double GearRatio=70;
int countsPerRev_motor=64;
int counts=0;
double RevsShaft2Rad=2*PI;
unsigned long t_ms=0.0;
double t=0.0;
double t_old=0.0;
double Pos1=0.0;
double Vel1=0.0;
float Dist1=0.0;
double WheelD=7.7;
double Pos_old1=0.0;
double Pos2=0.0;
double Vel2=0.0;
float Dist2=0.0;
double Pos_old2=0.0;
double specDist = 120.0;
double E1 = 0;
double E2 = 0;
float Rot1 = 0.0;
float Rot2 = 0.0;
char serialByte;


void setup() {
  // put your setup code here, to run once:
   //md.init();                      //initialize motor controller
Serial.begin(9600);
}

void loop() {
double tm = micros()/1000000.0;  //current time
// put your main code here, to run repeatedly:
//Serial.print(myEnc1.read());
//Serial.print("\t");
//Serial.print(myEnc2.read());
//Serial.print("\t");
//Serial.println();

t_ms = millis();
t = t_ms/1000.0;

E1=myEnc1.read()*(RevsShaft2Rad);
E2=myEnc2.read()*(RevsShaft2Rad);
Pos1=(((E1/countsPerRev_motor)/GearRatio)*RevsShaft2Rad);
Pos2=(((E2/countsPerRev_motor)/GearRatio)*RevsShaft2Rad);
Rot1=Pos1/39.66;
Rot2=Pos2/39.66;
Dist1=Rot1*9.8*3.14;
Dist2=Rot2*9.8*3.14;
Serial.print(Dist1);
Serial.print("\t");
Serial.print(Dist2);
Serial.print("\t");
Serial.println();


Vel1=(Pos1-Pos_old1)/(t-t_old);
Vel2=(Pos2-Pos_old2)/(t-t_old);
t_old=t;
Pos_old1=Pos1;
Pos_old2=Pos2;

   //if (Serial.available() > 0) {
   //  serialByte = Serial.read();
   //}

   //if (serialByte == 's') {
      //Serial.print(Dist1);
      //Serial.print("\t");
      //Serial.print(Dist2);
      //Serial.print("\t");
      //Serial.println();
      if(Dist1<specDist){
      digitalWrite(dir1,1);
      digitalWrite(en1,1);
      analogWrite(pwm1,100);
      delay(10);
      }
      if(Dist2<specDist){
      digitalWrite(dir2,1);
      digitalWrite(en2,1);
      analogWrite(pwm2,100);
      delay(10);
    }
    if(Dist1>=specDist){
      digitalWrite(dir1,1);
      digitalWrite(en1,1);
      analogWrite(pwm1,0);
      delay(10);
    }
    if(Dist2>=specDist){
      digitalWrite(dir2,1);
      digitalWrite(en2,1);
      analogWrite(pwm2,0);
      delay(10);
    }
  //}

//Serial.print(Vel);
//Serial.print("\t");
//Serial.println();
}

