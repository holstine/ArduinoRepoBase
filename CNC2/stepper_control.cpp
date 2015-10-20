#include "stepper_control.h"
#include "init.h"
//init our variables
long max_delta; 
double X_STEPS_PER_INCH;
double X_STEPS_PER_MM ;


double Y_STEPS_PER_INCH ;
double Y_STEPS_PER_MM ;

double Z_STEPS_PER_INCH;
double Z_STEPS_PER_MM ;

//default to inches for units
double xStepsPerUnit = X_STEPS_PER_MM;
double yStepsPerUnit = Y_STEPS_PER_MM;
double zStepsPerUnit = Z_STEPS_PER_MM;
double curve_section = CURVE_SECTION_MM;

//our direction vars
int x_direction = 1;  // 1 is positive direction, 0 is negitive direction
int y_direction = 1;
int z_direction = 1;



void init_steppers()
{
	//turn them off to start.
	disable_steppers();

	// THE MATH HERE SEEMS EASIER TO REPRESENT
	//  BUT THE MATH ON #DEFINED ELEMENTS RUNS OUT OF PRESISION TOO QUICK
	X_STEPS_PER_INCH = (X_MOTOR_STEPS );
	X_STEPS_PER_INCH *=THREADS_PER_INCH;
	X_STEPS_PER_MM   = (X_STEPS_PER_INCH);
	X_STEPS_PER_MM *=INCH_PER_MM;

	Y_STEPS_PER_INCH = (Y_MOTOR_STEPS );
	Y_STEPS_PER_INCH *=THREADS_PER_INCH;
	Y_STEPS_PER_MM   = (Y_STEPS_PER_INCH);
	Y_STEPS_PER_MM *=INCH_PER_MM;
	
	Z_STEPS_PER_INCH = (Z_MOTOR_STEPS );
	Z_STEPS_PER_INCH *=THREADS_PER_INCH;
	Z_STEPS_PER_MM   = (Z_STEPS_PER_INCH);
	Z_STEPS_PER_MM *= INCH_PER_MM;

	//Serial.println("steps per mm");
	//Serial.println( Z_STEPS_PER_MM);
	//Serial.println( Z_STEPS_PER_INCH);
	
	//init our points.
//	current_units.x = 0.0;
//	current_units.y = 0.0;
//	current_units.z = 0.0;
//	target_units.x = 0.0;
//	target_units.y = 0.0;
//	target_units.z = 0.0;
	
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
	setPosition(0.0,0.0,0.0);
	//print();
	calculate_deltas();
	setMaxFeedRate();
}
void goTo(double x, double y, double z){

set_target(x,y,z);

	calculate_deltas();
	dda_move();
}
void dda_move()
{
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

void moveAlongCurve( double cx, double cy, double cz, 
double fx, double fy, double fz, bool clockwise)
{ 
	float angleA, angleB, angle, radius, length, aX, aY, bX, bY;

	aX = ( getUnitsX() - cx);
	aY = ( getUnitsY() - cy);
	bX = (fx - cx);
	bY = (fy - cy);
	
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

	FloatPoint newPoint;
	for (s = 1; s <= steps; s++) {
		step = (!clockwise) ? s : steps - s; // Work backwards for CW
		newPoint.x = cx + radius * cos(angleA + angle * ((float) step / steps));
		newPoint.y = cy + radius * sin(angleA + angle * ((float) step / steps));
		goTo(newPoint.x, newPoint.y, newPoint.z);
 
		// Make step 
	}
	
}

bool can_step(int min_pin, int  max_pin, long current, long target, int direction)
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

void do_step(int step_pin)
{
	digitalWrite(step_pin, HIGH);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(5);
}

bool read_switch(int pin)
{
	return digitalRead(pin) ^ SENSORS_INVERTING ;
}

bool canXStep(){
	return can_step(X_MIN_PIN, X_MAX_PIN, current_steps.x, target_steps.x, x_direction); 
}

bool canYStep(){
	return	 can_step(Y_MIN_PIN, Y_MAX_PIN, current_steps.y, target_steps.y, y_direction); 
}

bool canZStep(){
	return  can_step(Z_MIN_PIN, Z_MAX_PIN, current_steps.z, target_steps.z, z_direction);
}

// ********************************
// converts from mm or inches to steps of the stepper motor
long to_steps(double steps_per_unit, double units){  
	return steps_per_unit * units;
}

double to_units(double steps_per_unit, double steps){  
	
	return steps / steps_per_unit ;
}

void set_target(double x, double y, double z)
{
	target_steps.x = to_steps(xStepsPerUnit, x);
	target_steps.y = to_steps(yStepsPerUnit, y);
	target_steps.z = to_steps(zStepsPerUnit, z);
	
	calculate_deltas();
}

void setPosition(double x, double y, double z)
{
	current_steps.x = to_steps(xStepsPerUnit, x);
	current_steps.y = to_steps(yStepsPerUnit, y);
	current_steps.z = to_steps(zStepsPerUnit, z);
	
	calculate_deltas();
}


double getUnitsX(){
	return to_units(xStepsPerUnit, current_steps.x);
}

double getUnitsY(){
	return to_units(yStepsPerUnit, current_steps.y);
}

double getUnitsZ(){
	return to_units(zStepsPerUnit, current_steps.z);
}

void calculate_deltas()
{
	delta_steps.x = abs(target_steps.x - current_steps.x);
	delta_steps.y = abs(target_steps.y - current_steps.y);
	delta_steps.z = abs(target_steps.z - current_steps.z);
	
	setDirection();
}
void setDirection(){
//what is our direction
	setXDirection (target_steps.x > current_steps.x);
	setYDirection (target_steps.y > current_steps.y);
	setZDirection(target_steps.z > current_steps.z);
}

void setXDirection(int dir){
	x_direction = dir;
	digitalWrite(X_DIR_PIN, dir ^ X_INVERT);
}

void setYDirection(int dir){
	y_direction = dir;
	digitalWrite(Y_DIR_PIN, dir ^ Y_INVERT);
}

void setZDirection(int dir){
	z_direction = dir;
	digitalWrite(Z_DIR_PIN, dir ^ Z_INVERT);
}

 void setFeedRate(double feedRate){
     myFeedRateDelay= calculate_feedrate_delay(feedRate);
	 	
}

 void setMaxFeedRate(){
    myFeedRateDelay= getMinDelay();
}

void delaySteppers(long feedRateDelay){
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

long calculate_feedrate_delay(double feedrate){	
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
	Serial.print("delay: ");
		Serial.println(delay);
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

long getMinDelay()
{
	return MINIMUMSTEPPERDELAY;
}

void setInches(){
	xStepsPerUnit = X_STEPS_PER_INCH;
	yStepsPerUnit = Y_STEPS_PER_INCH;
	zStepsPerUnit = Z_STEPS_PER_INCH;
	curve_section = CURVE_SECTION_INCHES;
	calculate_deltas();
}

void setMillimeters(){
	xStepsPerUnit = X_STEPS_PER_MM;
	yStepsPerUnit = Y_STEPS_PER_MM;
	zStepsPerUnit = Z_STEPS_PER_MM;
	curve_section = CURVE_SECTION_MM;
	calculate_deltas();
}


void disable_steppers()
{
	//enable our steppers
	//digitalWrite(X_ENABLE_PIN, LOW);
	//digitalWrite(Y_ENABLE_PIN, LOW);
//	digitalWrite(Z_ENABLE_PIN, LOW);
}

 void goToZMax(){ 
	setZDirection(1);
	println("Waiting for ZMax");
	while (!digitalRead(Z_MAX_PIN ) ){
		do_step(Z_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}   
	goTo(getUnitsX(), getUnitsY(), Z_RESET_LOCATION);
	setPosition(getUnitsX(), getUnitsY(), Z_RESET_LOCATION); 
	println("Z finished");
}
void goToZMin(){ 
	setZDirection(0);
	println("Waiting for ZMin");
	while (!digitalRead(Z_MIN_PIN ) ){
		do_step(Z_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}   
	goTo(getUnitsX(), getUnitsY(),0);
	setPosition(getUnitsX(), getUnitsY(), Z_TOUCH_OFF_LOCATION); 
	println("Z finished");
}
 void goToYMin(){
	setYDirection(0);
	println("Waiting for YMin");
	while (!digitalRead(Y_MIN_PIN )){
		do_step(Y_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}
	goTo(getUnitsX(), Y_RESET_LOCATION, getUnitsZ()); 
	setPosition(getUnitsX(), Y_RESET_LOCATION, getUnitsZ()); 
	println("Y finished");
}

 void goToXMin(){
	setXDirection(0);
		println("Waiting for XMin");
	while (!digitalRead(X_MIN_PIN) ){
		do_step(X_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}
	goTo( X_RESET_LOCATION, getUnitsY(),getUnitsZ()); 
	setPosition( X_RESET_LOCATION, getUnitsY(),getUnitsZ()); 
	println("X finished");
	
}

void goToTouchOff(){
	goTo(
		X_TOUCH_OFF_LOCATION,
		Y_TOUCH_OFF_LOCATION,
		Z_RESET_LOCATION);
	
	goToZMin();
	setPosition( 
		X_TOUCH_OFF_LOCATION,
		Y_TOUCH_OFF_LOCATION,
		Z_TOUCH_OFF_LOCATION); 
	goTo(
		X_TOUCH_OFF_LOCATION,
		Y_TOUCH_OFF_LOCATION,
		Z_TOUCH_OFF_LOCATION +1);
}

void resetLocation(){
	goToZMax(); // go to max height to keep bit out of the way
	goToYMin();
	goToXMin(); 
}
 

