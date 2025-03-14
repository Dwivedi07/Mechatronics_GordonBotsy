
#include "motor_drive.h"
#include "global.h"
#include <Metro.h>

#define STOP_BOT_INTERVAL     500 
static Metro metTimer4 = Metro(STOP_BOT_INTERVAL);

// ----------------- Module Variables
// int motorL_speed = 0.65 * motorL_MAXSPD; 
// int motorR_speed = 0.65 * motorR_MAXSPD; 
int turntimethreshold = 300;
int higherTurnSpeed = 180;
int lowerTurnSpeed = 0;
int turnTime = 950;
int turnTimePot = 950;
int stopTime = 500;

int motorL_speed = 0;
int motorR_speed = 0;
// ----- Module Main Functions
void motor_drive(int leftSpeed, int rightSpeed) {  
    // Control Left Motor
    if (leftSpeed > 0) {    
        digitalWrite(LIN1, LOW);
        digitalWrite(LIN2, HIGH);
        analogWrite(PWML, leftSpeed);
    } else if (leftSpeed < 0) {  
        digitalWrite(LIN1, HIGH);
        digitalWrite(LIN2, LOW);
        analogWrite(PWML, -leftSpeed);
    } else {
        digitalWrite(LIN1, LOW);
        digitalWrite(LIN2, LOW);
        analogWrite(PWML, 0);
    }

    // Control Right Motor
    if (rightSpeed > 0) {    
        digitalWrite(RIN1, LOW);
        digitalWrite(RIN2, HIGH);
        analogWrite(PWMR, rightSpeed);
    } else if (rightSpeed < 0) {  
        digitalWrite(RIN1, HIGH);
        digitalWrite(RIN2, LOW);
        analogWrite(PWMR, -rightSpeed);
    } else {
        digitalWrite(RIN1, LOW);
        digitalWrite(RIN2, LOW);
        analogWrite(PWMR, 0);
    }

  // Serial.print(leftSpeed);
  // Serial.print("`````");
  // Serial.println(rightSpeed);
}


void turn_by(int leftSpeed, int rightSpeed,int StartTime){ 
    while (millis() - StartTime <= turnTimePot) { 
        motor_drive(leftSpeed, rightSpeed);
    }
}

void handleStopBot(){
  // 500 corresponds to 64 ms
  static bool stop_flag = 0;

  if(!stop_flag){
    metTimer4.reset();
    stop_flag = 1;
  }
  motor_drive(0, 0);

  if(metTimer4.check()){
    state = next_state;
    stop_flag = 0;
  }
    


}




