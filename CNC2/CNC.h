// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef CNC_H_
#define CNC_H_
#include "Arduino.h"
//add your includes for the project CNC here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project CNC here
int initSDCard();
void testSDCard();
void getFile();
int processGCodeFile(char* filename);
//int readGLine(File file, char * gline);
void setSplash();

//Do not add code below this line
#endif /* CNC_H_ */
