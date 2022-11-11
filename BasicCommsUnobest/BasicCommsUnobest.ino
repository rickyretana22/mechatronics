#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3); // RX, TX
int button = 13;
char inByte = '1';

void setup()  
{
  // Open serial communications with computer and wait for port to open:
  Serial.begin(9600);

  // Print a message to the computer through the USB
  Serial.println("Hello Computer!");

  // Open serial communications with the other Arduino board
  mySerial.begin(9600);

  // Send a message to the other Arduino board
  mySerial.print("Hello other Arduino!");

}

void loop() // run over and over
{
if(Serial.available()){
  mySerial.write(Serial.read());
}
if(mySerial.available()){
  Serial.write(mySerial.read());
  delay(2);
  if(!mySerial.available()){
    Serial.println();
  }
}
}
