#include "global.h"
#include "servo.h"

// ------------Module Variables
int pos_servo = 0;                     // Servo position
bool increasing_servo = true;           // Direction flag

unsigned long previousMillis_Servo = 0;
const unsigned long intrvl_Servo = 30;  // 20ms update interval

// ----------------------------Main functions

void rotateservo() {
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis_Servo >= intrvl_Servo) {
        previousMillis_Servo = currentMillis;

        // Move servo smoothly in the current direction
        if (increasing_servo) {
            pos_servo+=5;
            if (pos_servo >= 180) increasing_servo = false; // Reverse at max angle
        } else {
            pos_servo-=5;
            if (pos_servo <= 0) increasing_servo = true;  // Reverse at min angle
        }

        servo1.write(pos_servo); // Move servo to new position
    }
}
