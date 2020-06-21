//  AUTHOR: Rob Tillaart & MFS version: @hpsaturn
// VERSION: 0.1.2
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL:
// HISTORY:
// 0.1.0 initial version
// 0.1.2 Multi functional Shield support
//
// Released to the public domain
#include <MultiFuncShield.h>
#include <Servo.h>
#include <Wire.h>

Servo mservo6;
Servo mservo9;

int pos = 0;

void checkStopConditions(byte btn) {

    MFS.manualDisplayRefresh();
    MFS.isrCallBack();

    if (btn == BUTTON_1_PRESSED || btn == BUTTON_1_LONG_PRESSED) {
        Serial.println("btn1");
    } else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED) {
        Serial.println("btn2");
    } else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED) {
        Serial.println("btn3");
    }

    int16_t x = (int16_t)(analogRead(POT_PIN) / 10);
    MFS.write(analogRead(x));
    //MFS.beep(1, x, 1);  // beep 1 times, 800 milliseconds on / 1000 off
}

void display(int value) {
    MFS.write(value);
}

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println("==============================");
    Serial.println("====== SERVO MFS TEST  ======");
    Serial.println("==============================");

    mservo6.attach(6);
    mservo9.attach(9);

    // Timer1.initialize();
    // MFS.initialize(&Timer1);  // initialize multifunction shield library
    MFS.initialize();  // initialize multifunction shield library
    MFS.write(0);
    Serial.println("== Multi Function Shield ready");
}

bool toggle;

void servoLoop() {
    static uint_fast32_t timeStamp = 0;
    if (millis() - timeStamp > 15) {
        timeStamp = millis();
        // in steps of 1 degree
        mservo6.write(pos);  // tell servo to go to position in variable 'pos'
        mservo9.write(pos);  // tell servo to go to position in variable 'pos'
        if (pos > 180 || pos == 0) toggle = !toggle;
        if (toggle) pos++;
        else pos--;
    }
}

void loop() {
    servoLoop();
    byte btn = MFS.getButton();
    checkStopConditions(btn);
}
