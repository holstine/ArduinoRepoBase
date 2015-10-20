/*
 * Stepper_state.h
 *
 *  Created on: Jun 23, 2012
 *      Author: Michael
 */

#ifndef STEPPER_STATE_H_
#define STEPPER_STATE_H_

#include "Arduino.h"

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

//FloatPoint current_units;
//FloatPoint target_units;
//FloatPoint delta_units;

LongPoint current_steps;
LongPoint target_steps;
LongPoint delta_steps;

double myFeedRateDelay;
double nominalFeedRate;
boolean abs_mode = true;   //0 = incremental; 1 = absolute





#endif /* STEPPER_STATE_H_ */
