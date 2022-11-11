
#define dir1 7
#define dir2 8
#define pwm1 9
#define pwm2 10
#define en1 2
#define en2 4
float sensorValues=0;

void setup() {
  // put your setup code here, to run once:
//configure the sensor
  pinMode(A8,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A8));
  sensorValues=analogRead(A8);
  // put your main code here, to run repeatedly:

//read raw sensor values
  

  //print the sensor values as numbers from 0 to 2500, where 0 means maximum
  //relectance and 2500 means minimum reflectance
  Serial.println("Drive Straight");
  digitalWrite(en1,1);
  digitalWrite(dir1,1);
  digitalWrite(en2,1);
  digitalWrite(dir2,1);
  analogWrite(pwm2,100);
  analogWrite(pwm1,100);
  if(sensorValues >= 150){
    analogWrite(pwm2,0);
    analogWrite(pwm1,0);
    delay(10);
  } 
}
