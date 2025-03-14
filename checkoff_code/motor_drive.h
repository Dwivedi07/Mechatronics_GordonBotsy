#ifndef MOTOR_DRIVE_H
#define MOTOR_DRIVE_H
#include "global.h"
#include <Arduino.h>


extern States_t state;
// Motor Control Pins
// Left motor pins
#define LIN1 13  
#define LIN2 7
#define PWML 6

// Right motor pins
#define RIN1 A0
#define RIN2 A1
#define PWMR 5

// Speed Constants
#define motorL_MAXSPD 250
#define motorR_MAXSPD 250

// #define motorL_speed //0.63*motorL_MAXSPD //03/03 0.68
// #define motorR_speed //0.63*motorR_MAXSPD


// Function Prototypes
void motor_drive(int leftSpeed, int rightSpeed);
void turn_by(int leftSpeed, int rightSpeed, int StartTime);
void stop_by(int StartTime);
void handleStopBot();

#endif // MOTOR_DRIVE_H

