// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef AVC_H_
#define AVC_H_
#include "Arduino.h"
//add your includes for the project AVC here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project AVC here



void breaks();
void updateWaypoint();
void steer();
void flash();
void turn(int deg);
void go ();
void backup ();
void stops();
int readOdo();
int readProx();
float readCompass();
void updatePosition();
void updateCurrentPosition();
void printState();

//Do not add code below this line
#endif /* AVC_H_ */
