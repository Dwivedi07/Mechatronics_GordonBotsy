#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include "global.h"

// ------------------------ Module Variables
extern unsigned long previousMillis_US;
extern const unsigned long intrvl_US;
extern float US_front_dist;
extern volatile long duration;

// ------------------------ Function Prototypes
void triggerUltrasonic();
void readUltrasonic();
void updateUltrasonic();
bool CheckifNearPotUltrasonic();

void triggerUltrasonicLeft();
void readUltrasonicLeft();
void updateUltrasonicLeft();

#endif // ULTRASONIC_H
