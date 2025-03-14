#include "ultrasonic.h"
#include "global.h"
#include "motor_drive.h" 

// ------------------------Module Variables
unsigned long previousMillis_US = 0;
const unsigned long intrvl_US = 100;  // Read every 100ms
float US_front_dist = 0;
volatile long duration = 0;

float US_left_dist = 0;
volatile long duration_left = 0;
//int ultrasonic_threshold = 3; //in cm

// ------------------------Main functions
void triggerUltrasonic() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
}

void triggerUltrasonicLeft(){
  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
   delayMicroseconds(10);
  digitalWrite(TRIG_PIN_LEFT, LOW);
}

void readUltrasonicLeft(){
   duration_left = pulseIn(ECHO_PIN_LEFT, HIGH, 30000); // 30ms timeout (~5m max distance)
    if (duration_left > 0) {
        US_left_dist = duration_left * 0.034 / 2;  // Convert to cm
    }
}
void readUltrasonic() {
    duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout (~5m max distance)
    if (duration > 0) {
        US_front_dist = duration * 0.034 / 2;  // Convert to cm
    }
   
}

void updateUltrasonicLeft() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_US >= intrvl_US) {
        previousMillis_US = currentMillis;
        triggerUltrasonicLeft();
        readUltrasonicLeft();
        // Serial.println(US_front_dist);
    }
}

void updateUltrasonic() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_US >= intrvl_US) {
        previousMillis_US = currentMillis;
        triggerUltrasonic();
        readUltrasonic();
        // Serial.println(US_front_dist);
    }
}

bool CheckifNearPotUltrasonic(){\

  if(US_left_dist <= 24){
    motor_drive(0,0);
    return 1;
  }
  return 0;
}