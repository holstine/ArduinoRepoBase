/*
 * stepper_control.h
 *
 *  Created on: Jun 23, 2012
 *      Author: Michael
 */

#ifndef STEPPER_CONTROL_H_
#define STEPPER_CONTROL_H_

#include "Arduino.h"

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


double getUnitsX();

double getUnitsY();

double getUnitsZ();
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


#endif /* STEPPER_CONTROL_H_ */
