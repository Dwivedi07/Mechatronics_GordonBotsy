#include <Arduino.h>  // Required to use millis()
#include "beacon.h"
#include "motor_drive.h"
#include "global.h"

//------------------------- Module Variables
volatile bool rightDetected = false;
volatile bool leftDetected = false;
volatile unsigned long lastRightDetectionTime = 0;
volatile unsigned long lastLeftDetectionTime = 0;
const int DETECTION_HOLD_TIME = 500;

int max_threshold_so_far = 0;


const int NUM_READINGS = 10; // Number of readings to average
unsigned int readings[NUM_READINGS] = {0}; // Array to store readings
int readIndex = 0;
unsigned int total = 0;


// Pot Vars
unsigned int maxAnalogValue = 0; // To store the maximum observed value
unsigned long lastResetTime = 0; // To reset max value periodically
const unsigned long RESET_INTERVAL = 300; // Interval to reset max value (450ms)
float x = 1;  // Set the value of x between 0 and 1
const unsigned int THRESHOLD = x * 750;  // Calculate threshold based on x

// -------------------------------------Main Functions

// Interrupt Service Routines (ISR)
void rightISR() { 
    rightDetected = true; 
    lastRightDetectionTime = millis();
}

void leftISR() { 
    leftDetected = true; 
    lastLeftDetectionTime = millis();
}

void handleBeaconDetection() {
    unsigned long currentTime = millis();
    //Serial.println(rightDetected);
    // Reset detections if they haven't been seen recently
    if (currentTime - lastRightDetectionTime > DETECTION_HOLD_TIME) {
        rightDetected = false;
    }
    if (currentTime - lastLeftDetectionTime > DETECTION_HOLD_TIME) {
        leftDetected = false;
    }

    // Movement logic prioritizing the most recent detection
    if (rightDetected) {
        Serial.println("Pot Has been detected");
        

        next_state = STATE_LINE_TRACKING_WITH_ULTRASONIC_DETECTION; //STATE_LINE_SEARCH;
        state = STATE_STOP_BOT;
        return;
        
    } else {
        Serial.println("Searching... Rotating 360");
        motor_drive(0.72 * motorL_MAXSPD, -0.72 * motorR_MAXSPD);
         //motor_drive(0, 0);
    }
}

// bool CheckifNearPot(){
//     // Pot Detection Part:   // Read analog input from the left sensor
//     unsigned int analogValue = analogRead(fuckingLeftEyeAnalog);
//     static bool threshold_flag = 0;
//     // Check if this reading is the new maximum

//     if(analogValue > 700){
//       return 0;
//     }
//      // Update moving average
//     total -= readings[readIndex]; // Subtract the oldest reading
//     readings[readIndex] = analogValue; // Store new reading
//     total += readings[readIndex]; // Add new reading to total
//     readIndex = (readIndex + 1) % NUM_READINGS; // Move to next index
    
//     unsigned int avgAnalogValue = total / NUM_READINGS;

//       // Check if this averaged reading is the new maximum
//     // if (avgAnalogValue > maxAnalogValue) {
//     //     maxAnalogValue = avgAnalogValue;
//     // }

//     max_threshold_so_far = min(max(avgAnalogValue,max_threshold_so_far),747);

//     Serial.print(max_threshold_so_far);
//     Serial.print(" Average Analog Value of Last N readings: ");
//     Serial.print(avgAnalogValue);
//     // Serial.print(" Maximum Analog Value: ");
//     // Serial.print(maxAnalogValue);
//     Serial.println(",");
//     // Print the maximum observed value and status periodically
//     if (millis() - lastResetTime >= RESET_INTERVAL) {
        

//         // if (maxAnalogValue >= THRESHOLD){
//         //   threshold_flag = 1;
//         // } 
        
//         if(avgAnalogValue>490 && avgAnalogValue < 0.99*max_threshold_so_far){// && threshold_flag){
//             // Serial.println("time to turn into the pot");
//             return 1;
//         } 
    
//         maxAnalogValue = 0; // Reset max value for next interval
//         lastResetTime = millis(); // Reset the timer

//     }

//     return 0;
// }