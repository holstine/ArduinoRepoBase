/*
 * init.h
 *
 *  Created on: Jun 23, 2012
 *      Author: Michael
 */

#ifndef INIT_H_
#define INIT_H_
#include "Arduino.h"



#define COMMAND_SIZE 128
#define GFILENAME  "gcode.txt"
#define MM_PER_INCH   25.40
#define INCH_PER_MM 0.0393700787
#define THREADS_PER_INCH   18

#define MOTOR_STEPS    200
#define X_MOTOR_STEPS    800
#define Y_MOTOR_STEPS    800
#define Z_MOTOR_STEPS    800
// define the parameters of our machine.

#define X_RESET_LOCATION   0
#define Y_RESET_LOCATION   0
#define Z_RESET_LOCATION   40


#define X_TOUCH_OFF_LOCATION   36
#define Y_TOUCH_OFF_LOCATION   430
#define Z_TOUCH_OFF_LOCATION   28

#define X_INVERT   1
#define Y_INVERT   1
#define Z_INVERT   0


//our maximum feedrates (larger number is slower for stepper delay)
//200 is way too fast for my steppers
#define  MINIMUMSTEPPERDELAY 300


// Units in curve section
#define CURVE_SECTION_INCHES 0.019685
#define CURVE_SECTION_MM 0.5

// Set to one if sensor outputs inverting (ie: 1 means open, 0 means closed)
// RepRap opto endstops are *not* inverting.
#define SENSORS_INVERTING 0



// How many temperature samples to take.  each sample takes about 100 usecs.
#define TEMPERATURE_SAMPLES 5


//cartesian bot pins
#define X_STEP_PIN 5
#define Y_STEP_PIN 6
#define Z_STEP_PIN 7


#define X_DIR_PIN 2
#define Y_DIR_PIN 3
#define Z_DIR_PIN 4

#define X_MIN_PIN A0
#define X_MAX_PIN A3


#define Y_MIN_PIN A1
#define Y_MAX_PIN A4

#define Z_MIN_PIN A2
#define Z_MAX_PIN A5


#define X_ENABLE_PIN 14
#define Y_ENABLE_PIN 14
#define Z_ENABLE_PIN 14

//extruder pins
#define EXTRUDER_MOTOR_SPEED_PIN   11
#define EXTRUDER_MOTOR_DIR_PIN     12
#define EXTRUDER_HEATER_PIN        6
#define EXTRUDER_FAN_PIN           5
#define EXTRUDER_THERMISTOR_PIN    0  //a -1 disables thermistor readings
#define EXTRUDER_THERMOCOUPLE_PIN  -1 //a -1 disables thermocouple readings


typedef struct  {
	double x;
	double y;
 	double z;
} FloatPoint ;


  typedef struct  {
	long x;
	long y;
 	long z;
} LongPoint;


#endif /* INIT_H_ */
