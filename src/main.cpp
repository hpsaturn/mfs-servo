//  AUTHOR: Rob Tillaart & MFS version: @hpsaturn
// VERSION: 0.1.2
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL:
// HISTORY:
// 0.1.0 initial version
// 0.1.2 Multi functional Shield support
//
// Released to the public domain

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <Servo.h>

Servo mservo;
int pos = 0;

void display(int value){
  MFS.write(value);
}

void setup()
{
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println("==============================");
    Serial.println("====== SERVO MFS TEST  ======");
    Serial.println("==============================");

    Timer1.initialize();
    MFS.initialize(&Timer1);    // initialize multifunction shield library
    MFS.write(0);
    Serial.println("== Multi Function Shield ready");

    mservo.attach(9);

}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    display(pos);
    mservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    display(pos);
    mservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
//
// END OF FILE
//
