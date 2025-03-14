#include "motor_drive.h"
#include "global.h"
#include "ultrasonic.h"
#include "pot_movement.h"
#include "linefollow.h"
#include <Metro.h>

#define LEFT_TURN_INTERVAL 9500
static Metro metTimer3 = Metro(LEFT_TURN_INTERVAL);


// ---------------------Main Functions
void handleEngagePot(){
    /*
    We will follow following steps:
    1- Turn 90 left
    2 - Move straight till: Ultrasonic sensor reading that can be accessed by global variable-US_front_dist
         is less than threshold: ultrasonic_threshold
    3 -  StopInstantaneuosly as the value is less than the threshold
    4- Turn 90 left

    1- Turn 180 deg
    
    */
    // int StartTime = millis();
     
    // handle
    // motor_drive(motorL_speed, motorR_speed);
    // if (US_front_dist <= ultrasonic_threshold){
    //      secondTurn
    // }
         
  }
    
void handleMovePot(){
  motor_drive(210, 200);
  static bool us_flag = 0;

  if(!us_flag){
    metTimer1.reset();
    us_flag = 1;
  }

  if(US_front_dist <= ultrasonic_threshold && metTimer1.check()){
    motor_drive(0,0);
    state = STATE_UNLOAD;
  }
}

void handleUnload(){
    // StartTime = millis();
    // turn_by(lowerTurnSpeed, higherTurnSpeed, StartTime);
    servo1.write(180); 
    delay(3000);
    //servo1.write(0); 
  
    state = STATE_BOT_OFF;
    
    
}

void handle180degLeftTurn(){
   //replace while loops in line tracking

  static bool flag = 0;

  if(!flag){
    metTimer3.reset();
    flag = 1;
  }

  int leftSpeed = lowerTurnSpeed;
  int rightSpeed = higherTurnSpeed;

  motor_drive(leftSpeed, rightSpeed+70);
  

  if(metTimer3.check()){
    state = STATE_MOVE_POT;
  }
}