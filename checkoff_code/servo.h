#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <Servo.h>
#include "global.h"

// ------------------------ Module Variables
extern int pos_servo;
extern bool increasing_servo;
extern unsigned long previousMillis_Servo;
extern const unsigned long intrvl_Servo;
//extern Servo servo1;  // Declare the servo object

// ------------------------ Function Prototypes
void rotateservo();

#endif // SERVO_CONTROL_H
