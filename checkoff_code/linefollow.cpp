#include "ultrasonic.h"
#include "motor_drive.h"
#include "global.h"
#include "linefollow.h"
#include "beacon.h"
#include <Metro.h>


#define MOTOR_TURN_TIME_INTERVAL     5000  // 5000 corresponds to 600 ms nearly
#define DETECTION_HOLD_OFF_INTERVAL  20000

static Metro metTimer1 = Metro(MOTOR_TURN_TIME_INTERVAL);
static Metro metTimer2 = Metro(DETECTION_HOLD_OFF_INTERVAL);

// ---------------------Module Vars
float KP = 0.018;//0.055
float KD = 0.1;//0.75;//0.25
int error = 0;
int prev_error=0;

 // ----------------------Main Functions

void handleLineSearch(){
  // keep rotating left untill the mid IRval_3 is 1 and then stop by
  motor_drive(-1*higherTurnSpeed,higherTurnSpeed);  
  if (IRval_1 or IRval_2 or IRval_3 or IRval_4 or IRval_5){
    int StartTime = millis();
    
    next_state = STATE_LINE_TRACKING_WITH_DETECTION;
    state = STATE_STOP_BOT;
  }

}


void handleLineTracking(){
  // IRval_5 is rightmost
  // ir led off means->IRval = 1 -> line is there
  // ir led on means-> IRval = 0 -> no line
  int position = 0;
  bool turningZ = false; 
  unsigned long turnStartTime = 0;


  position =-1000*(1 - IRval_1) + (-1*1000*(1-IRval_2) + 0*(1-IRval_3) + 1*1000*(1-IRval_4)) + (1000)*(1 - IRval_5) ;
  
  int error =  0 - position;
  float adjust = error * KP + KD * (error - prev_error);
  prev_error = error;
    
  int leftSpeed = motorL_speed + adjust;
  int rightSpeed = motorR_speed - adjust;

  // Apply constraints manually
  leftSpeed = max(-200, min(200, leftSpeed));
  rightSpeed = max(-200, min(200, rightSpeed));
  // Serial.print(leftSpeed);
  // Serial.print("`````");
  // Serial.println(rightSpeed);
  // when anyone of the side led is off -> button (1 or 5's) state 1 start turning
  // but if you are deteting midled also off -> button 3's state 1 no turn
  if ((IRval_1 && IRval_2 && IRval_3 && IRval_4 && IRval_5) || (!IRval_1 && !IRval_2 && !IRval_3 && !IRval_4 && !IRval_5)){
    motor_drive(leftSpeed+10, rightSpeed+10);
    return;
  }


  if ((IRval_1 && IRval_2 && IRval_3) || (IRval_5 && IRval_4 && IRval_3)) { 
    // just these flags doesn't impy this is a turn
    // the case when bot is line followng and it overshoots from the line how will we detect that as not turning
    turningZ = true;  // Start the turn
    
    state = STATE_TURN;
    return;
    
  }
  motor_drive(leftSpeed, rightSpeed);
  return;
}

void handleLineTrackingWithUltrasonicDetection(){
  static bool flag = 0;
  static bool hold_off_flag = 0;

   static bool ignition_flag = 0;

  if(!ignition_flag){
    servo2.write(180);
    delay(2000);
    servo2.write(90);
    delay(2000);
    servo2.write(0);
    delay(2000);
    // servo2.write(90);
    // delay(2000);
    // servo2.write(180);
    delay(2000);
    ignition_flag = 1;
  }

  Serial.println(hold_off_flag);
  Serial.println(US_left_dist);
  if(!flag){
    metTimer2.reset();
    flag = 1;
  }
  if(!hold_off_flag){
    //Serial.println("Hold off Phase");
    motorL_speed =  0.63*motorL_MAXSPD; //03/03 0.68
    motorR_speed = 0.63*motorR_MAXSPD;
  }
  if(metTimer2.check()){
    hold_off_flag = 1;
    motorL_speed =  0.68*motorL_MAXSPD; //03/03 0.68
    motorR_speed = 0.68*motorR_MAXSPD;
  }
  
  if(hold_off_flag){
    if (CheckifNearPotUltrasonic()){
      // Serial.println("Performing a 180");
      //next_state = STATE_180_DEG_LEFT_TURN;
      //state = STATE_BOT_OFF;
      state = STATE_180_DEG_LEFT_TURN;
      return;
    }
  }
  Serial.println(state);
  handleLineTracking();
  
}

// void handleLineTrackingWithDetection(){

//   static bool flag = 0;
//   static bool hold_off_flag = 0;

//   static bool ignition_flag = 0;

//   if(!ignition_flag){
//     servo2.write(180);
//     delay(2000);
//     servo2.write(90);
//     delay(2000);
//     servo2.write(0);
//     delay(2000);
//     // servo2.write(90);
//     // delay(2000);
//     // servo2.write(180);
//     delay(2000);
//     ignition_flag = 1;
//   }
//   if(!flag){
//     metTimer2.reset();
//     flag = 1;
//   }
//   if(!hold_off_flag){
//     Serial.println("Hold off Phase");
//     motorL_speed =  0.63*motorL_MAXSPD; //03/03 0.68
//     motorR_speed = 0.63*motorR_MAXSPD;
//   }
//   if(metTimer2.check()){
//     hold_off_flag = 1;
//     motorL_speed =  0.68*motorL_MAXSPD; //03/03 0.68
//     motorR_speed = 0.68*motorR_MAXSPD;
//   }
//   // Check if near the pot sufficient to transition to engage mode
//   if(hold_off_flag){
//     if (CheckifNearPot()){
//       // Serial.println("Performing a 180");
//       //next_state = STATE_180_DEG_LEFT_TURN;
//       //state = STATE_STOP_BOT;
//       state = STATE_180_DEG_LEFT_TURN;
//       return;
//     }
//   }
 
//   handleLineTracking();
// }


void handleTurn(){
  //replace while loops in line tracking
  

  static bool flag = 0;
  static int leftSpeed = 0;
  static int rightSpeed = 0;
  // Serial.print("flag");
  // Serial.println(flag);
  if(!flag){
    metTimer1.reset();
    flag = 1;

    if (IRval_5){
      leftSpeed = higherTurnSpeed;
      rightSpeed = lowerTurnSpeed;
      // Serial.println(" here in IR2");
    }
    else if(IRval_1){
      leftSpeed = lowerTurnSpeed;
      rightSpeed = higherTurnSpeed;
      // Serial.println(" here in IR1"); 
    }
  }

  motor_drive(leftSpeed, rightSpeed);
  if(metTimer1.check()){
    // Serial.println("Timer Expired for STATE TURN");
    state = STATE_LINE_TRACKING_WITH_DETECTION;
  }
  
}

