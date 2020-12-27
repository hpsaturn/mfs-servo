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

Servo mservo_pin6;
Servo mservo_pin9;

#define MAX_ANGLE 150
#define MIN_ANGLE 20

uint16_t pos = MIN_ANGLE;
bool stop = true;
uint16_t servo_delay = 45;

void display(int value) {
    MFS.write(value);
}

void mfsLoop() {

    byte btn = MFS.getButton();
    MFS.manualDisplayRefresh();
    MFS.isrCallBack();

    if (btn == BUTTON_1_PRESSED || btn == BUTTON_1_LONG_PRESSED) {
        Serial.print("==> btn stop: ");
        stop = !stop;
        Serial.println(stop);
        if (stop) MFS.beep(3, 4, 3, 3); 
        else MFS.beep(1, 1, 3, 3, 1); 
        delay(100);
    } else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED) {
        Serial.print("==> btn- delay: ");
        if (servo_delay > 0) servo_delay--;
        Serial.println(servo_delay);
    } else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED) {
        Serial.print("==> btn+ delay: ");
        if (servo_delay < 255) servo_delay++;
        Serial.println(servo_delay);
    }
    
    display(servo_delay);

}

void setup() {
    Serial.begin(115200);
    delay(10);
    Serial.println();
    Serial.println("================================");
    Serial.println("====== SERVO MFS TESTER  =======");
    Serial.println("================================");

    mservo_pin6.attach(6);
    mservo_pin9.attach(9);

    // Timer1.initialize();
    // MFS.initialize(&Timer1);  // initialize multifunction shield library
    MFS.initialize();  // initialize multifunction shield library
    Serial.println("");
    Serial.println("Parameters:");Serial.println("");
    Serial.print("MAX_ANGLE: ");  Serial.println(MAX_ANGLE);
    Serial.print("MIN_ANGLE: ");  Serial.println(MIN_ANGLE);
    Serial.print("INIT DELAY: "); Serial.println(servo_delay);
    Serial.println("");
    Serial.println("=== Multi Function Shield ready ===");
}

bool toggle;

void servoLoop() {
    static uint_fast32_t timeStamp = 0;
    if (millis() - timeStamp > servo_delay) {
        timeStamp = millis();
        // in steps of 1 degree
        mservo_pin6.write(pos);  // tell servo to go to position in variable 'pos'
        mservo_pin9.write(pos);  // tell servo to go to position in variable 'pos'
        if (pos == MAX_ANGLE || pos == MIN_ANGLE) toggle = !toggle;
        if (toggle) pos++;
        else pos--;
    }
}

void logLoop() {
    static uint_fast32_t timeStamp = 0;
    if (millis() - timeStamp > 500) {
        timeStamp = millis();
        Serial.print("angle: "); Serial.print(pos);
        Serial.print(" delay: "); Serial.println(servo_delay);
    }
}

void loop() {
    if (!stop) {
        servoLoop();
        logLoop();
    }
    mfsLoop();
}
