/*
 * CNCMachine.h
 *
 *  Created on: Jul 9, 2012
 *      Author: Michael
 */

#ifndef CNCMACHINE_H_
#define CNCMACHINE_H_

#include "Point.h"
#include "Arduino.h"
class CNCMachine {

	Point current_steps;
	Point target_steps;
	Point delta_steps;

	double myFeedRateDelay;
	double X_STEPS_PER_INCH;
	double X_STEPS_PER_MM;

	double Y_STEPS_PER_INCH;
	double Y_STEPS_PER_MM;

	double Z_STEPS_PER_INCH;
	double Z_STEPS_PER_MM;

	//default to inches for units
	double xStepsPerUnit;
	double yStepsPerUnit;
	double zStepsPerUnit;
	double curve_section;
	int x_direction; // 1 is positive direction, 0 is negitive direction
	int y_direction;
	int z_direction;

	double max_delta;

public:
	CNCMachine();
	virtual ~CNCMachine();

	virtual void init();
	virtual Point getCurrentPosition();
	virtual void goTo(Point point);
	virtual void goToOrigin();
	virtual void setPosition(Point position);
	virtual void setFeedRate(double feedRate);
	virtual void setMaxFeedRate();
	virtual void moveAlongCurve(Point center, Point target, bool clockwise);
	virtual void setInches();
	virtual void setMillimeters();
	virtual void toolPower(bool on);

private:
	long to_steps(double steps_per_unit, double units);
	double to_units(double steps_per_unit, double steps);
	void calculate_deltas();
	void set_target(Point p);
	void setDirection();
	void setXDirection(int dir);
	void setYDirection(int dir);
	void setZDirection(int dir);
	void moveMachine();
	bool can_step(int min_pin, int max_pin, long current, long target,
			int direction);
	void do_step(int step_pin);
	bool read_switch(int pin);
	bool canXStep();
	bool canYStep();
	bool canZStep();
	void delaySteppers(long feedRateDelay);
	long calculate_feedrate_delay(double feedrate);
	long getMinDelay();
	double getUnitsX();
	double getUnitsY();
	double getUnitsZ();
};

#endif /* CNCMACHINE_H_ */
