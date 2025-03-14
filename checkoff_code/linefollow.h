#ifndef LINE_FOLLOW_H
#define LINE_FOLLOW_H
#include "global.h"
#include <Arduino.h>
#include <Metro.h>
#include "motor_drive.h"  // Include motor control functions


extern Metro metTimer1;

extern States_t state;
// IR sensor values (assumed to be defined elsewhere)
extern int IRval_1;
extern int IRval_2;
extern int IRval_3;
extern int IRval_4;
extern int IRval_5;

// Ultrasonic sensor values (if used in transitions)
extern int ultrasonic_threshold;
extern int US_front;

// Previous error for PID control (assumed to be tracked in the function)
extern int prev_error_line_tracking;

// // Function declarations
void handleLineTracking();
void handleLineSearch();
void handleLineTrackingWithDetection();
void handleLineTrackingWithUltrasonicDetection();



void handleTurn();
#endif // LINE_FOLLOW_H
