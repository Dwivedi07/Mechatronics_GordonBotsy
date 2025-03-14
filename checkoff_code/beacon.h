#ifndef BEACON_H
#define BEACON_H
#include "global.h"
#include <Arduino.h>

// Function Prototypes

extern States_t state;
void rightISR();
void leftISR();
void handleBeaconDetection();
// bool CheckifNearPot();

#endif // BEACON_DETECTION_H
