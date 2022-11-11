char inByte='1';
int led = 13;
#define dir1 7
#define dir2 8
#define pwm1 9
#define pwm2 10
#define en1 2
#define en2 4

float rangeValues=0;
QTRSensors qtr;
int Bias[] = {140,68,68,68,68,68,68,68,68,68};
const uint8_t SensorCount = 11;

uint16_t sensorValues[SensorCount];
  float SumAS = 0;
  float SumA = 0;
  float lineloc;

void setup()  
{
  pinMode(A8,INPUT);
  pinMode(led, OUTPUT);
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){38,39,40,41,42,43,44,45,46,47,48}, SensorCount);
  qtr.setEmitterPin(2);
  // Open serial communications with computer and wait for port to open:
  Serial.begin(9600);

  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");

  // Open serial communications with the other Arduino board
  Serial2.begin(9600);

  // Send a message to the other Arduino board
  Serial2.print("Hello other Arduino!");

  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(en1,OUTPUT);
  pinMode(en1,OUTPUT);
}

void loop() // run over and over
{
if(Serial.available()){
  Serial2.write(Serial.read());
}
if(Serial2.available()){
  Serial.write(Serial2.read());
  delay(10);
  inByte = Serial2.read();
  
    if (inByte == '4')
    {
      digitalWrite(led, 1);
      Serial.write("4 has been selected");
      delay(1000);
      rangeValues=analogRead(A8);
      Serial.println("Drive Straight");
      digitalWrite(en1,1);
      digitalWrite(dir1,1);
      digitalWrite(en2,1);
      digitalWrite(dir2,1);
      analogWrite(pwm2,100);
      analogWrite(pwm1,100);
      if(rangeValues >= 150){
        analogWrite(pwm2,0);
        analogWrite(pwm1,0);
        delay(10);
      } 
    }
    
    if (inByte == '5')
    {
      digitalWrite(led, 1);
      Serial.write("5 has been selected");
      delay(1000);
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
      analogWrite(pwm2,60);
      analogWrite(pwm1,45);
      delay(10);
    }
    if(lineloc >= 1){
      Serial.println("Turn Right");
      digitalWrite(en1,1);
      digitalWrite(dir1,1);
      digitalWrite(en2,1);
      digitalWrite(dir2,1);
      analogWrite(pwm2,45);
      analogWrite(pwm1,60);
      delay(10);
    }
    if(lineloc >= -1 && lineloc <=1){
      Serial.println("Drive Straight");
      digitalWrite(en1,1);
      digitalWrite(dir1,1);
      digitalWrite(en2,1);
      digitalWrite(dir2,1);
      analogWrite(pwm2,50);
      analogWrite(pwm1,50);
      delay(10);
    }
    Serial.println(lineloc);
 
    Serial.println();
    delay(250);
  SumAS = 0;
  SumA = 0;
  }
   if (inByte == '6')
    {  
      analogWrite(pwm1,0);
      analogWrite(pwm2,0);
    }
  else
    {
      digitalWrite(led, 0);
    }
  if(!Serial2.available()){
    Serial.println();
    }
}
}
