/*
 * CNCMachine.cpp
 *
 *  Created on: Jul 9, 2012
 *      Author: Michael
 */

#include "CNCMachine.h"

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

CNCMachine::CNCMachine() {
	// TODO Auto-generated constructor stub

}

CNCMachine::~CNCMachine() {
	// TODO Auto-generated destructor stub787889897
}

void CNCMachine::init() {
	//turn them off to start.
//	disable_steppers();

	current_steps = Point();

	// THE MATH HERE SEEMS EASIER TO REPRESENT
	//  BUT THE MATH ON #DEFINED ELEMENTS RUNS OUT OF PRESISION TOO QUICK
	X_STEPS_PER_INCH = (X_MOTOR_STEPS);
	X_STEPS_PER_INCH *= THREADS_PER_INCH;
	X_STEPS_PER_MM = (X_STEPS_PER_INCH);
	X_STEPS_PER_MM *= INCH_PER_MM;

	Y_STEPS_PER_INCH = (Y_MOTOR_STEPS);
	Y_STEPS_PER_INCH *= THREADS_PER_INCH;
	Y_STEPS_PER_MM = (Y_STEPS_PER_INCH);
	Y_STEPS_PER_MM *= INCH_PER_MM;

	Z_STEPS_PER_INCH = (Z_MOTOR_STEPS);
	Z_STEPS_PER_INCH *= THREADS_PER_INCH;
	Z_STEPS_PER_MM = (Z_STEPS_PER_INCH);
	Z_STEPS_PER_MM *= INCH_PER_MM;
	curve_section = CURVE_SECTION_MM;
	//our direction vars
	x_direction = 1; // 1 is positive direction, 0 is negitive direction
	y_direction = 1;
	z_direction = 1;
	//Serial.println("steps per mm");
	//Serial.println( Z_STEPS_PER_MM);
	//Serial.println( Z_STEPS_PER_INCH);

	//init our points.

	pinMode(X_STEP_PIN, OUTPUT);
	pinMode(X_DIR_PIN, OUTPUT);
	//pinMode(X_ENABLE_PIN, OUTPUT);
	pinMode(X_MIN_PIN, INPUT);
	pinMode(X_MAX_PIN, INPUT);

	pinMode(Y_STEP_PIN, OUTPUT);
	pinMode(Y_DIR_PIN, OUTPUT);
	//pinMode(Y_ENABLE_PIN, OUTPUT);
	pinMode(Y_MIN_PIN, INPUT);
	pinMode(Y_MAX_PIN, INPUT);

	pinMode(Z_STEP_PIN, OUTPUT);
	pinMode(Z_DIR_PIN, OUTPUT);
	//pinMode(Z_ENABLE_PIN, OUTPUT);
	pinMode(Z_MIN_PIN, INPUT);
	pinMode(Z_MAX_PIN, INPUT);

	//figure our stuff.

	setMillimeters();
	setPosition(Point());
	//print();
	calculate_deltas();
	setMaxFeedRate();

}
Point CNCMachine::getCurrentPosition() {
	return Point();
}

void CNCMachine::goTo(Point p) {

	set_target (p);
	calculate_deltas();
	moveMachine();
}

void CNCMachine::goToOrigin() {
	goTo(Point());
}

void CNCMachine::setPosition(Point position) {
	current_steps.x = to_steps(xStepsPerUnit, position.x);
	current_steps.y = to_steps(yStepsPerUnit, position.y);
	current_steps.z = to_steps(zStepsPerUnit, position.z);

	calculate_deltas();
}

void CNCMachine::setFeedRate(double feedRate) {
	   myFeedRateDelay= calculate_feedrate_delay(feedRate);
}

void CNCMachine::setMaxFeedRate() {
	   myFeedRateDelay=  getMinDelay();
}

void CNCMachine::moveAlongCurve(Point c, Point f, bool clockwise) {
	float angleA, angleB, angle, radius, length, aX, aY, bX, bY;

	aX = ( getUnitsX() - c.x);
	aY = ( getUnitsY() - c.y);
	bX = (f.x - c.x);
	bY = (f.y - c.y);

	if (clockwise) { // Clockwise
		angleA = atan2(bY, bX);
		angleB = atan2(aY, aX);
	} else { // Counterclockwise
		angleA = atan2(aY, aX);
		angleB = atan2(bY, bX);
	}
	// Make sure angleB is always greater than angleA
	// and if not add 2PI so that it is (this also takes
	// care of the special case of angleA == angleB,
	// ie we want a complete circle)
	if (angleB <= angleA) angleB += 2 * M_PI;
	angle = angleB - angleA;

	radius = sqrt(aX * aX + aY * aY);
	length = radius * angle;
	int steps, s, step;
	steps = (int) ceil(length / curve_section);

	Point newPoint;
	for (s = 1; s <= steps; s++) {
		step = (!clockwise) ? s : steps - s; // Work backwards for CW
		newPoint.x = c.x + radius * cos(angleA + angle * ((float) step / steps));
		newPoint.y = c.y + radius * sin(angleA + angle * ((float) step / steps));
		goTo(newPoint);

		// Make step
	}

}

void CNCMachine::setInches() {
	xStepsPerUnit = X_STEPS_PER_INCH;
	yStepsPerUnit = Y_STEPS_PER_INCH;
	zStepsPerUnit = Z_STEPS_PER_INCH;
	curve_section = CURVE_SECTION_INCHES;
	calculate_deltas();
}

void CNCMachine::setMillimeters() {
	xStepsPerUnit = X_STEPS_PER_MM;
	yStepsPerUnit = Y_STEPS_PER_MM;
	zStepsPerUnit = Z_STEPS_PER_MM;
	curve_section = CURVE_SECTION_MM;
	calculate_deltas();
}

void CNCMachine::toolPower(bool on) {
}

void CNCMachine::set_target(Point p) {
	target_steps.x = to_steps(xStepsPerUnit, p.x);
	target_steps.y = to_steps(yStepsPerUnit, p.y);
	target_steps.z = to_steps(zStepsPerUnit, p.z);

	calculate_deltas();
}

// ********************************
// converts from mm or inches to steps of the stepper motor
long  CNCMachine::to_steps(double steps_per_unit, double units){
	return steps_per_unit * units;
}

double  CNCMachine::to_units(double steps_per_unit, double steps){

	return steps / steps_per_unit ;
}


void CNCMachine::calculate_deltas()
{
	delta_steps.x = abs(target_steps.x - current_steps.x);
	delta_steps.y = abs(target_steps.y - current_steps.y);
	delta_steps.z = abs(target_steps.z - current_steps.z);

	setDirection();
}

void CNCMachine::setDirection(){
//what is our direction
	setXDirection (target_steps.x > current_steps.x);
	setYDirection (target_steps.y > current_steps.y);
	setZDirection(target_steps.z > current_steps.z);
}

void CNCMachine::setXDirection(int dir){
	x_direction = dir;
	digitalWrite(X_DIR_PIN, dir ^ X_INVERT);
}

void CNCMachine::setYDirection(int dir){
	y_direction = dir;
	digitalWrite(Y_DIR_PIN, dir ^ Y_INVERT);
}

void CNCMachine::setZDirection(int dir){
	z_direction = dir;
	digitalWrite(Z_DIR_PIN, dir ^ Z_INVERT);
}

void CNCMachine::moveMachine(){
	//enable our steppers
		//digitalWrite(X_ENABLE_PIN, HIGH);
		//digitalWrite(Y_ENABLE_PIN, HIGH);
		//digitalWrite(Z_ENABLE_PIN, HIGH);

		//figure out our deltas
		max_delta = max(delta_steps.x, delta_steps.y);
		max_delta = max(delta_steps.z, max_delta);

		//init stuff.
		long x_counter = -max_delta/2;
		long y_counter = -max_delta/2;
		long z_counter = -max_delta/2;

		//our step flags
		bool x_can_step = 0;
		bool y_can_step = 0;
		bool z_can_step = 0;



		//do our DDA line!
		do
		{

			x_can_step = canXStep();
			y_can_step = canYStep();
			z_can_step = canZStep();

			if (x_can_step)
			{
				x_counter += delta_steps.x;

				if (x_counter > 0)
				{
					do_step(X_STEP_PIN);
					x_counter -= max_delta;

					if (x_direction){
						current_steps.x++;
					}else{
						current_steps.x--;
					}
				}
			}

			if (y_can_step)
			{
				y_counter += delta_steps.y;

				if (y_counter > 0)
				{
					do_step(Y_STEP_PIN);
					y_counter -= max_delta;

					if (y_direction)
					current_steps.y++;
					else
					current_steps.y--;
				}

			}

			if (z_can_step)
			{
				z_counter += delta_steps.z;
				if (z_counter > 0)
				{
					do_step(Z_STEP_PIN);
					z_counter -= max_delta;

					if (z_direction)
					current_steps.z++;
					else
					current_steps.z--;
				}

			}

			//extruder_manage_temperature();
			//wait for next step.
			delaySteppers(myFeedRateDelay);
		}while (x_can_step || y_can_step || z_can_step);

		//set our points to be the same
		//current_units.x = target_units.x;
		//current_units.y = target_units.y;
		//current_units.z = target_units.z;
		calculate_deltas();

}


bool CNCMachine::can_step(int min_pin, int  max_pin, long current, long target, int direction)
{
	//stop us if we're on target
	if (target == current){
		return false;
	}
	//stop us if we're at home and still going
	 if (read_switch(min_pin) && !direction){
		//Serial.println(min_pin);
	//	Serial.println(read_switch(min_pin) );
	//	Serial.println(direction) ;
	//Serial.println("hit minimum pin");
		return false;
	}
	//stop us if we're at max and still going
	 if (read_switch(max_pin) && direction){
		//Serial.println(min_pin);
		//Serial.println(read_switch(min_pin) );
		//Serial.println(direction) ;
		//Serial.println("hit maximum pin");
		return false;
	}
	//default to being able to step
	return true;
}

void CNCMachine::do_step(int step_pin)
{
	digitalWrite(step_pin, HIGH);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(5);
}

bool CNCMachine::read_switch(int pin)
{
	return digitalRead(pin) ^ SENSORS_INVERTING ;
}

bool CNCMachine::canXStep(){
	return can_step(X_MIN_PIN, X_MAX_PIN, current_steps.x, target_steps.x, x_direction);
}

bool CNCMachine::canYStep(){
	return	 can_step(Y_MIN_PIN, Y_MAX_PIN, current_steps.y, target_steps.y, y_direction);
}

bool CNCMachine::canZStep(){
	return  can_step(Z_MIN_PIN, Z_MAX_PIN, current_steps.z, target_steps.z, z_direction);
}

void  CNCMachine::delaySteppers(long feedRateDelay){
	long milliDelay =0;
	if (feedRateDelay >= 16383){
		milliDelay = feedRateDelay / 1000;
	}
	//	Serial.print("feedRateDelay: ");
	//	Serial.println(feedRateDelay);
		if (milliDelay > 0)
		delay(milliDelay);
		else
		delayMicroseconds(feedRateDelay);
}

long CNCMachine::calculate_feedrate_delay(double feedrate){



	// feedrate is in (units)/minute
	// feed rate is speed it takes to go 1 unit of distance (D/T)
	// feedRateDelay is how long to wait between steps (T/S)
	// (D/S) is distance per step
	// So conversion is 1/(D/T) *(D/S) = (T/S)
	// or feedRateDelay = 1/feedRate * 1/stepPerUnit
	//  just use zsteps for now
	// This really should use the hypotonuse but doesn't need to be that acurate yet
	if(feedrate == 0) return getMinDelay();
	double delay = 1.0/to_steps(zStepsPerUnit, feedrate) ;
	delay = delay * 60*1000000; // convert from minutes to microseconds
//	Serial.print("delay: ");
//		Serial.println(delay);
	if(delay < getMinDelay()) delay = getMinDelay();
	return delay;
	/*
	double distance = sqrt(delta_units.x*delta_units.x + delta_units.y*delta_units.y + delta_units.z*delta_units.z);
	long master_steps = 0;

	//find the dominant axis.
	if (delta_steps.x > delta_steps.y)
	{
		if (delta_steps.z > delta_steps.x)
		master_steps = delta_steps.z;
		else
		master_steps = delta_steps.x;
	}
	else
	{
		if (delta_steps.z > delta_steps.y)
		master_steps = delta_steps.z;
		else
		master_steps = delta_steps.y;
	}

	//calculate delay between steps in microseconds.  this is sort of tricky, but not too bad.
	//the formula has been condensed to save space.  here it is in english:
	// distance / feedrate * 60000000.0 = move duration in microseconds
	// move duration / master_steps = time between steps for master axis.
	double delay = ((distance * 60000000.0) / feedrate) / master_steps;
	if(delay < getMaxSpeed()) delay = getMaxSpeed();
	return delay;
	*/
}


long CNCMachine::getMinDelay()	{
		return MINIMUMSTEPPERDELAY;
	}

double  CNCMachine::getUnitsX(){
	return to_units(xStepsPerUnit, current_steps.x);
}

double  CNCMachine::getUnitsY(){
	return to_units(yStepsPerUnit, current_steps.y);
}

double  CNCMachine::getUnitsZ(){
	return to_units(zStepsPerUnit, current_steps.z);
}


