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

const int bluePin = 28;
const int greenPin = 26;
const int redPin = 24;
const int blockDet = 25;


void setup() {
  // Start serial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for a serial port connection before continuing.
  }

  pinMode(bluePin, OUTPUT);  digitalWrite(bluePin, HIGH);
  pinMode(greenPin, OUTPUT); digitalWrite(greenPin, HIGH);
  pinMode(redPin, OUTPUT);   digitalWrite(redPin, HIGH);
  pinMode(A3, INPUT);

}

void loop() {
  delay(100);
  
    /*Serial.println("");
    Serial.println("Blue, Green, Red");
  *

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
  //colorNumR=colorNumR/10;
  //colorNumG=colorNumG/10;
  //colorNumB=colorNumB/10;
  // turn off LED and wait for another cycle
  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, HIGH);
  delay(200);

  hallVal=analogRead(A3);
  if (hallVal >=512 || hallVal <=508){
    Serial.println("MAGNET BLOCK");
    hallMem=1;
  }
  else{
    if (cB>150 && cB<200 && cR>50 && cR<100 && cG>80 && cG<125){
    Serial.println("Blue Block Detected");
    Serial.println(cB);
    Serial.println(cR);
    Serial.println(cG);
    }
    else if(cR > 150){
    Serial.println("Red Block Detected");
    Serial.println(cB);
    Serial.println(cR);
    Serial.println(cG);
    }
    else if(cG > 125 && cG< 200){
    Serial.println("Green Block Detected");
    Serial.println(cB);
    Serial.println(cR);
    Serial.println(cG);
    }
    else{
    Serial.println("No Block");
    Serial.println(cB);
    Serial.println(cR);
    Serial.println(cG);
    }
  }
  }
