#include <QTRSensors.h>

#define dir1 7
#define dir2 8
#define pwm1 9
#define pwm2 10
#define en1 2
#define en2 4

QTRSensors qtr;
int Bias[] = {130,68,68,68,68,68,68,68,68,68};

const uint8_t SensorCount = 11;
uint16_t sensorValues[SensorCount];

  float SumAS = 0;
  float SumA = 0;
  float lineloc;

void setup() {
  // put your setup code here, to run once:
//configure the sensors
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){38,39,40,41,42,43,44,45,46,47,48}, SensorCount);
  qtr.setEmitterPin(2);

  Serial.begin(9600);

  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

//read raw sensor values
  qtr.read(sensorValues);

  //print the sensor values as numbers from 0 to 2500, where 0 means maximum
  //relectance and 2500 means minimum reflectance
 
  for(uint8_t i = 0; i<SensorCount; i++)
  {
    //Serial.print(sensorValues[i]);
    //Serial.print('\t');
  }
  Serial.println();
  delay(250);


  //print the sensor values as numbers from 0 to 2500, where 0 means maximum
  //relectance and 2500 means minimum reflectance
  
  for(uint8_t i = 0; i<SensorCount-1; i++)
  {
    Serial.print(sensorValues[i]-Bias[i]);
    Serial.print('\t');
  }


  for(int i = 0; i<SensorCount-1; i++)
  {
    SumAS = SumAS+(sensorValues[i]-Bias[i])*(i+1);
    SumA = SumA+sensorValues[i]-Bias[i];
  }
  lineloc = SumAS/SumA;
  lineloc = lineloc-6;
  if(lineloc <= -1){
    Serial.println("Turn Left");
    digitalWrite(en1,1);
    digitalWrite(dir1,1);
    digitalWrite(en2,1);
    digitalWrite(dir2,1);
    analogWrite(pwm2,30);
    analogWrite(pwm1,10);
    delay(10);
  }
  if(lineloc >= 1){
    Serial.println("Turn Right");
    digitalWrite(en1,1);
    digitalWrite(dir1,1);
    digitalWrite(en2,1);
    digitalWrite(dir2,1);
    analogWrite(pwm2,0);
    analogWrite(pwm1,40);
    delay(10);
  }
  if(lineloc >= -1 && lineloc <=1){
    Serial.println("Drive Straight");
    digitalWrite(en1,1);
    digitalWrite(dir1,1);
    digitalWrite(en2,1);
    digitalWrite(dir2,1);
    analogWrite(pwm2,20);
    analogWrite(pwm1,20);
    delay(10);
  }
  Serial.println(lineloc);
 
  Serial.println();
  delay(250);
SumAS = 0;
SumA = 0;
}

