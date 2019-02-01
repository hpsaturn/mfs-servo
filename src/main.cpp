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

void display(float value){
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
  delay(100);

}
//
// END OF FILE
//
