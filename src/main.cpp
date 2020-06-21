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

#define MAX_ANGLE 175
#define MIN_ANGLE 20

int pos = MIN_ANGLE;
bool stop = false;
int servo_delay = 45;

void display(int value) {
    MFS.write(value);
}

void checkButtons(byte btn) {

    MFS.manualDisplayRefresh();
    MFS.isrCallBack();

    if (btn == BUTTON_1_PRESSED || btn == BUTTON_1_LONG_PRESSED) {
        Serial.println("btn1");
        MFS.beep(3, 4, 3, 3); 
        stop = !stop;
        delay(100);
    } else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED) {
        Serial.println("btn2");
        if (servo_delay < 255) servo_delay++;
    } else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED) {
        Serial.println("btn3");
        if (servo_delay > 0) servo_delay--;
    }
    
    display(servo_delay);

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
    if (millis() - timeStamp > servo_delay) {
        timeStamp = millis();
        // in steps of 1 degree
        mservo6.write(pos);  // tell servo to go to position in variable 'pos'
        mservo9.write(pos);  // tell servo to go to position in variable 'pos'
        if (pos == MAX_ANGLE || pos == MIN_ANGLE) toggle = !toggle;
        if (toggle) pos++;
        else pos--;
    }
}

void loop() {
    if (!stop) servoLoop();
    byte btn = MFS.getButton();
    checkButtons(btn);
}
