#ifndef GLOBAL_H
#define GLOBAL_H
#include <Servo.h>
#include <Arduino.h>


//------------------ STATE DEFINITION ------------------
typedef enum {
  STATE_BOT_OFF,              //0
  STATE_BEACON_DETECTION_AND_IGNITION,//1
  STATE_LINE_SEARCH,//2
  STATE_LINE_TRACKING,//3
  STATE_LINE_TRACKING_WITH_DETECTION,//4
  STATE_ENGAGE_POT,//5
  STATE_MOVE_POT,//6
  STATE_UNLOAD,//7
  STATE_TURN_OFF_IGNITION,//8
  STATE_TURN,//9
  STATE_180_DEG_LEFT_TURN, //10
  STATE_STOP_BOT, //11
  STATE_LINE_TRACKING_WITH_ULTRASONIC_DETECTION //12
} States_t;

//------------------ GLOBAL VARIABLES ------------------
// Declare the global state variable as extern (defined in .ino)
extern States_t state;
extern States_t next_state;

// IR Sensor values
extern int IRval_1; 
extern int IRval_2;
extern int IRval_3;
extern int IRval_4;
extern int IRval_5;


extern int TIMER_INTERVAL_MS;
// Ultrasonic sensor values
extern float US_front_dist;
extern float US_left_dist;
extern int ultrasonic_threshold;

//
extern int max_threshold_so_far;
// Line tracking error
extern int prev_error_line_tracking;
// ---------------------------Motor Variables

extern int higherTurnSpeed;
extern int lowerTurnSpeed;
extern int turnTime;

extern int motorL_speed;
extern int motorR_speed;
//------------------ PIN DEFINITIONS ------------------
// Line sensor pins
#define IR1 8
#define IR2 9
#define IR3 10
#define IR4 11
#define IR5 12

// Pot sensor pins
#define RIGHT_SENSOR 2
//#define LEFT_SENSOR 3

//#define fuckingLeftEyeAnalog A2

// Motor Pins
#define LIN1 13  
#define LIN2 7
#define PWML 6

#define RIN1 A0
#define RIN2 A1
#define PWMR 5

// Ultrasonic sensor pin
#define TRIG_PIN A3
#define ECHO_PIN 4

// Ultrasonic sensor pin
#define TRIG_PIN_LEFT A2
#define ECHO_PIN_LEFT 3

//Servo Pins
#define Servo_1 A4 // Arm Servo 
#define Servo_2 A5 // Gate Servo

//Servo class
// Arm servo is servo 1 and gate servo is servo 2
extern Servo servo1, servo2; 

#endif // GLOBAL_H
