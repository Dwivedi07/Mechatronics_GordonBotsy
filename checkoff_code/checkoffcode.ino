
// #define USE_TIMER_1     true
#define USE_TIMER_2     true
#include "TimerInterrupt.h"
#include <ISR_Timer.h>
#include <Metro.h>
#include "motor_drive.h"
#include "beacon.h"
#include "global.h"
#include "linefollow.h"
#include "servo.h"
#include "pot_movement.h"
#include "ultrasonic.h"
/*---------------Module Defines-----------------------------*/


/*---------------Module Variables---------------------------*/


// /*---------------STATE DEFINITION-----------------------------*/
States_t state;
States_t next_state;
int IRval_1; 
int IRval_2;
int IRval_3;
int IRval_4;
int IRval_5;
int US_front;
int ultrasonic_threshold = 10;
int prev_error_line_tracking;

Servo servo1, servo2;

#define TIMER_INTERVAL_MS 50L;

/*---------------Main Functions----------------*/


void setup() {
 // put your setup code here, to run once:
  Serial.begin(9600);
  TCCR0B = TCCR0B & B11111000 | B00000010;

  // Pot setup initializations
  pinMode(RIGHT_SENSOR, INPUT);
  //pinMode(LEFT_SENSOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR), rightISR, RISING);
  //attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR), leftISR, RISING);

  // ITimer1.init();
 
  // Ultrasonic Initilaizations
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);


  //Servo Initilizations
  servo1.attach(Servo_1);
  servo2.attach(Servo_2);

  servo1.write(0);
  
  delay(2000);
  state = STATE_BEACON_DETECTION_AND_IGNITION;
  // start buzzer/fan
}

void loop() {
  Serial.print("Current state is :");
  Serial.println(state);
  //rotateservo();
  //Serial.println(state);
  if(state == STATE_LINE_TRACKING_WITH_ULTRASONIC_DETECTION){
    updateUltrasonicLeft();
  }

  if(state == STATE_MOVE_POT ){
    updateUltrasonic();
  }


  // Serial.print("Left Dist   ");
  // Serial.print(US_left_dist);
  // Serial.print("Front Dist   ");
  // Serial.println(US_front_dist);
  IRval_1 = digitalRead(IR1);
  IRval_2 = digitalRead(IR2);
  IRval_3 = digitalRead(IR3);
  IRval_4 = digitalRead(IR4);
  IRval_5 = digitalRead(IR5);

  //US_front = analogRead(US_F);

  //write code to read phototransistor values on every loop execution

  unsigned long currentTime = millis();

  switch (state) {
    case STATE_BOT_OFF:
      motor_drive(0, 0);
      break;

    case STATE_BEACON_DETECTION_AND_IGNITION:
      handleBeaconDetection();
      break;

    case STATE_LINE_SEARCH:
      handleLineSearch();
      break;

    //Line Tracking
    case STATE_LINE_TRACKING:
      handleLineTracking();
      break;

    // case STATE_LINE_TRACKING_WITH_DETECTION:
    //   handleLineTrackingWithDetection();
    //   break;

    case STATE_LINE_TRACKING_WITH_ULTRASONIC_DETECTION:
      handleLineTrackingWithUltrasonicDetection();
      break;
    // case STATE_ENGAGE_POT: 
    // // After detecting the exact location of pot to the left from bot we will stop there
    //   handleEngagePot();
    //   break;

    case STATE_MOVE_POT:
      handleMovePot();
      break;

    case STATE_UNLOAD:
      handleUnload();
      break;

    case STATE_TURN:
      handleTurn();
      break;

    case STATE_180_DEG_LEFT_TURN:
      handle180degLeftTurn();
      break;

    case STATE_STOP_BOT:
      handleStopBot();
      break;
    // case STATE_TURN_OFF_IGNITION:
    //   handleTurnOffIgnition();
    //   break;

    default:
      Serial.println("Unknown state encountered!");
      break;
  }


}




