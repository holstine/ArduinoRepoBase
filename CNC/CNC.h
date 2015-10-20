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


double getUnitsX();
double getUnitsY();
double getUnitsZ();

void println(char * string);
void println(double string);
void println(long string);
void print(char * string);
void print(double string);
void print(long string);
void resetLCD();
void clearLCD();
void print();
void printZ();
void printY();
void printX();
void lcdGoTo(int position);


int initSDCard();
void testSDCard();
void getFile();
int processGCodeFile(char* filename);
//int readGLine(File file, char * gline);
void setSplash();

//our feedrate variables.

//init our string processing
void init_process_string();

//Read the string and execute instructions
void process_string(char instruction[], int size);

//look for the number that appears after the char key and return it
double search_string(char key, char instruction[], int string_size);
//look for the command if it exists.
bool has_command(char key, char instruction[], int string_size);


void init_steppers();
void goTo(double x, double y, double z);
void dda_move();

void moveAlongCurve( double cx, double cy, double cz,
double fx, double fy, double fz, bool clockwise);

bool can_step(int min_pin, int  max_pin, long current, long target, int direction);

void do_step(int step_pin);

bool read_switch(int pin);

bool canXStep();
bool canYStep();

bool canZStep();

// ********************************
// converts from mm or inches to steps of the stepper motor
long to_steps(double steps_per_unit, double units);

double to_units(double steps_per_unit, double steps);

void set_target(double x, double y, double z);

void setPosition(double x, double y, double z);


void calculate_deltas();
void setDirection();

void setXDirection(int dir);

void setYDirection(int dir);

void setZDirection(int dir);

 void setFeedRate(double feedRate);

 void setMaxFeedRate();
void delaySteppers(long feedRateDelay);

long calculate_feedrate_delay(double feedrate);

long getMinDelay();
void setInches();

void setMillimeters();


void disable_steppers();

 void goToZMax();
void goToZMin();
 void goToYMin();
 void goToXMin();

void goToTouchOff();

void resetLocation();



//Do not add code below this line
#endif /* CNC_H_ */
