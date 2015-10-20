// Do not remove the include below
#include "CNC.h"
//#include "init.h"
//#include "stepper_control.h"
//#include "process_string.h"
//#include "LCDOutput.h"
#include "SD.h"
// Arduino G-code Interpreter
// redun by  Michael Holstine
// v1.0 by Mike Ellery - initial software (mellery@gmail.com)
// v1.1 by Zach Hoeken - cleaned up and did lots of tweaks (hoeken@gmail.com)
// v1.2 by Chris Meighan - cleanup / G2&G3 support (cmeighan@gmail.com)
// v1.3 by Zach Hoeken - added thermocouple support and multi-sample temp readings. (hoeken@gmail.com)

//#include <SD.h>

//our command string
// ***************************init.h *********************************************

double getUnitsX();
double getUnitsY();
double getUnitsZ();

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

typedef struct {
	double x;
	double y;
	double z;
} FloatPoint;

typedef struct {
	long x;
	long y;
	long z;
} LongPoint;

LongPoint current_steps;
LongPoint target_steps;
LongPoint delta_steps;

double myFeedRateDelay;
double nominalFeedRate;
boolean abs_mode = true; //0 = incremental; 1 = absolute

char foo[COMMAND_SIZE];
int serial_count;
int no_data = 0;

long max_delta;
double X_STEPS_PER_INCH;
double X_STEPS_PER_MM;

double Y_STEPS_PER_INCH;
double Y_STEPS_PER_MM;

double Z_STEPS_PER_INCH;
double Z_STEPS_PER_MM;

//default to inches for units
double xStepsPerUnit = X_STEPS_PER_MM;
double yStepsPerUnit = Y_STEPS_PER_MM;
double zStepsPerUnit = Z_STEPS_PER_MM;
double curve_section = CURVE_SECTION_MM;

//our direction vars
int x_direction = 1; // 1 is positive direction, 0 is negitive direction
int y_direction = 1;
int z_direction = 1;

double to_units(double steps_per_unit, double steps) {

	return steps / steps_per_unit;
}

double getUnitsX() {
	return to_units(xStepsPerUnit, current_steps.x);
}
double getUnitsY() {
	return to_units(yStepsPerUnit, current_steps.y);
}
double getUnitsZ() {
	return to_units(zStepsPerUnit, current_steps.z);
}

void clearLCD() {
//	Serial.print(0xFE, BYTE);
//	Serial.print(0x01, BYTE);
}

void lcdGoTo(int position) { //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
//	if (position<16){ Serial.print(0xFE, BYTE); //command flag
//		Serial.print((position+128), BYTE); //position
//	}else if (position<32){Serial.print(0xFE, BYTE); //command flag
//		Serial.print((position+48+128), BYTE); //position
//	} else { lcdGoTo(0); }
}

void setSplash() {
	clearLCD();
	lcdGoTo(3);
	Serial.print("Some text");
	lcdGoTo(17);
	Serial.print("Second line");
//	delay(100);
//	delay(5000);
	clearLCD();
}

void println(char * string) {
	clearLCD();
	lcdGoTo(0);
	Serial.println(string);
}

void println(double string) {
	clearLCD();
	lcdGoTo(0);
	Serial.println(string);
}

void println(long string) {
	clearLCD();
	lcdGoTo(0);
	Serial.println(string);
}

void print(char * string) {
	Serial.print(string);
}

void print(double string) {
	Serial.print(string);
}

void print(long string) {
	Serial.print(string);
}

void resetLCD() {
//	Serial.print(0x07, BYTE);
//	Serial.print(18, BYTE);
}

void printZ() {
	print("z  ");
	print(getUnitsZ());
//	print("s  ");
//	print(current_steps.z);
//	print("  t  ");
//	println(target_steps.z);
}
void printY() {
	print("y  ");
	print(getUnitsY());
//	print("s  ");
//	print(current_steps.y);
//	print("  t  ");
//	println(target_steps.y);
}
void printX() {
	print("x  ");
	print(getUnitsX());
//	print("s  ");
//	print(current_steps.x);
//	print("  t  ");
//	println(target_steps.x);
}
void print() {
	printX();
	printY();
	printZ();
}

void setup() {
	clearLCD();
	Serial.begin(9600);
	println("start");
//	testSDCard();
//	if(!initSDCard()) return;

	init_steppers();
	println("resetLocation");
	resetLocation();
	println("touchOff");
	goToTouchOff();
	//	setSplash();

	int i = 0;

	//	init_extruder();
	init_process_string();
	int linesProcessed = processGCodeFile(GFILENAME);
	Serial.print("processed: ");
	Serial.println(linesProcessed);
}

int initSDCard() {

	Serial.print("Initializing SD card...");
	pinMode(8, OUTPUT);

	if (!SD.begin(4)) {
		Serial.println("SD initialization failed!");
		return 0;
	}
	  testSDCard();
	Serial.println("initialization done.");
	return 1;
}

// once gcode file is read then the rest can be done by serial terminal if needed
void loop() {
	char c;
	//keep it hot!
	//	extruder_manage_temperature();
	//read in characters if we got them.
	if (Serial.available() > 0) {
		c = Serial.read();
		no_data = 0;
		//newlines are ends of commands.
		if (c != '\n') {
			foo[serial_count] = c;
			serial_count++;
		}
	}
	//mark no data.
	else {
		no_data++;
		delayMicroseconds(100);
	}
	//if theres a pause or we got a real command, do it
	if (serial_count && (c == '\n' || no_data > 100)) {
		//process our command!
		process_string(foo, serial_count);

		//clear command.
		init_process_string();
	}
	//no data?  turn off steppers
	if (no_data > 1000)
		disable_steppers();
}
void testSDCard() {
	int linesProcessed = 0;
	File myFile = SD.open(GFILENAME);
	if (myFile) {
		Serial.println(GFILENAME);

		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			linesProcessed ++;
			Serial.write(myFile.read());
			if(linesProcessed > 1000) break;
		}
		// close the file:
		myFile.close();
	} else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}
void getFile() {

}


int readGLine(File file, char * gline){
	char c;
	int charcount =0;
	while(charcount < COMMAND_SIZE){
		c= file.read();
		if (c == '\n'){
			gline[charcount] = '\0';
			return charcount;
		}else{
			gline[charcount] = c;
			charcount++;
		}
	}

}
int processGCodeFile(char* filename) {
	int linesProcessed = 0;
	char  gline[COMMAND_SIZE];

	if (!SD.exists(GFILENAME)){
		Serial.print("error opening ");
		Serial.println(GFILENAME);
		return 0;
	}
	File file  = SD.open(filename);
	if (file) {
		Serial.println(GFILENAME);
	}

//	 read from the file until there's nothing else in it:
	while (file.available()) {
		linesProcessed ++;
		int cmdSize = readGLine(file, gline);
		println(gline);
		process_string(gline, cmdSize);

	}
	return linesProcessed;
}


// ************************************* processString.cpp *************************

//init our string processing
void init_process_string() {
	//init our command
//  for (byte i=0; i<COMMAND_SIZE; i++)
//    foo[i] = 0;
//  serial_count = 0;

}

//Read the string and execute instructions
void process_string(char instruction[], int size) {
	//the character / means delete block... used for comments and stuff.
	if (instruction[0] == '/' || instruction[0] == ';'
			|| instruction[0] == '#') {
		return;
	}

	FloatPoint target;
	FloatPoint currentPosition;
	currentPosition.x = getUnitsX();
	currentPosition.y = getUnitsY();
	currentPosition.z = getUnitsZ();

	byte code = 0;

	//Get Target

	target.x = currentPosition.x;
	target.y = currentPosition.y;
	target.z = currentPosition.z;
	if (has_command('X', instruction, size))
		target.x = search_string('X', instruction, size);
	if (has_command('Y', instruction, size))
		target.y = search_string('Y', instruction, size);
	if (has_command('Z', instruction, size))
		target.z = search_string('Z', instruction, size);

	if (!abs_mode) {
		target.x = currentPosition.x + search_string('X', instruction, size);
		target.y = currentPosition.y + search_string('Y', instruction, size);
		;
		target.z = currentPosition.z + search_string('X', instruction, size);
		;
	}
	//set our target.
	set_target(target.x, target.y, target.z);

	double feedrate = search_string('F', instruction, size);
	if (feedrate > 0)
		nominalFeedRate = feedrate;

	// handle no G code but has Coordinates remember the last feed rate
	if ((has_command('X', instruction, size)
			|| has_command('Y', instruction, size)
			|| has_command('Z', instruction, size))
			&& !has_command('G', instruction, size)) {
		//	setFeedRate(nominalFeedRate);
		goTo(target.x, target.y, target.z);

	}

	if (has_command('G', instruction, size)) {
		//which one?
		code = (int) search_string('G', instruction, size);
		switch (code) {
		//Rapid Positioning
		case 0:
			setMaxFeedRate();
			goTo(target.x, target.y, target.z);
			break;

			//Linear Interpolation
		case 1:
			setFeedRate(nominalFeedRate);
			goTo(target.x, target.y, target.z);
			break;

			//Clockwise arc
		case 2:
			//Counterclockwise arc
		case 3:
			FloatPoint cent;

			// Centre coordinates are always relative
			cent.x = search_string('I', instruction, size) + currentPosition.x;
			cent.y = search_string('J', instruction, size) + currentPosition.y;
			cent.z = target.z;
			bool clockwise;
			clockwise = (code == 2);

			moveAlongCurve(cent.x, cent.y, cent.z, target.x, target.y, target.z,
					clockwise);
			break;

		case 4:
			delay(1000 * (int) search_string('P', instruction, size));
			break;

			//Inches for Units
		case 20:
			setInches();
			break;

			//mm for Units
		case 21:
			setMillimeters();
			break;

			//go home.
		case 28:
			goTo(0.0, 0.0, 0.0);
			break;

			//go home via an intermediate point.
		case 30:
			setMaxFeedRate();
			goTo(target.x, target.y, target.z);
			//go home.
			goTo(0.0, 0.0, 0.0);
			break;

			//Absolute Positioning
		case 90:
			abs_mode = true;
			break;

			//Incremental Positioning
		case 91:

			abs_mode = false;
			break;

			//Set as home
		case 92:
			setPosition(0.0, 0.0, 0.0);
			break;

			/*
			 //Inverse Time Feed Mode
			 case 93:

			 break;  //TODO: add this

			 //Feed per Minute Mode
			 case 94:

			 break;  //TODO: add this
			 */

		default:
			Serial.print("huh? G");
//      Serial.println(code,DEC);
		}
	}

	if (has_command('F', instruction, size)) {
		double rate = search_string('F', instruction, size);
		setFeedRate(rate);
		nominalFeedRate = rate;

	}
	//find us an m code.
	if (has_command('M', instruction, size)) {
		code = search_string('M', instruction, size);
		switch (code) {
		//TODO: this is a bug because search_string returns 0.  gotta fix that.
		case 0:
			true;
			break;
			/*
			 case 0:
			 //todo: stop program
			 break;

			 case 1:
			 //todo: optional stop
			 break;

			 case 2:
			 //todo: program end
			 break;
			 */
			//set max extruder speed, 0-255 PWM
//    case 100:
//      extruder_speed = (int)(search_string('P', instruction, size));
//      break;
//
//      //turn extruder on, forward
//    case 101:
//      extruder_set_direction(1);
//      extruder_set_speed(extruder_speed);
//      break;
//
//      //turn extruder on, reverse
//    case 102:
//      extruder_set_direction(0);
//      extruder_set_speed(extruder_speed);
//      break;
//
//      //turn extruder off
//    case 103:
//      extruder_set_speed(0);
//      break;
//
//      //custom code for temperature control
//    case 104:
//      extruder_set_temperature((int)search_string('P', instruction, size));
//
//      //warmup if we're too cold.
//      while (extruder_get_temperature() < extruder_target_celsius)
//      {
//        extruder_manage_temperature();
//        Serial.print("T:");
//        Serial.println(extruder_get_temperature());
//        delay(1000);
//      }
//
//      break;
//
//      //custom code for temperature reading
//    case 105:
//      Serial.print("T:");
//      Serial.println(extruder_get_temperature());
//      break;
//
//      //turn fan on
//    case 106:
//      extruder_set_cooler(255);
//      break;
//
//      //turn fan off
//    case 107:
//      extruder_set_cooler(0);
//      break;
		default:
			Serial.print("Huh? M");
			Serial.println(code);
		}
	}

	//tell our host we're done.
	Serial.println("ok");
	//	Serial.println(line, DEC);
}

//look for the number that appears after the char key and return it
double search_string(char key, char instruction[], int string_size) {
	char temp[10] = "";

	for (byte i = 0; i < string_size; i++) {
		if (instruction[i] == key) {
			i++;
			int k = 0;
			while (i < string_size && k < 10) {
				if (instruction[i] == 0 || instruction[i] == ' ')
					break;

				temp[k] = instruction[i];
				i++;
				k++;
			}
			return strtod(temp, NULL);
		}
	}
	// if no key then return 0
	return 0;
}

//look for the command if it exists.
bool has_command(char key, char instruction[], int string_size) {
	for (byte i = 0; i < string_size; i++) {
		if (instruction[i] == key)
			return true;
	}

	return false;
}

// ********************************************** StepperControl *******************************

void init_steppers() {
	//turn them off to start.
	disable_steppers();

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
	setPosition(0.0, 0.0, 0.0);
	//print();
	calculate_deltas();
	setMaxFeedRate();
}
void goTo(double x, double y, double z) {

	set_target(x, y, z);

	calculate_deltas();
	dda_move();
}
void dda_move() {
	//enable our steppers
	//digitalWrite(X_ENABLE_PIN, HIGH);
	//digitalWrite(Y_ENABLE_PIN, HIGH);
	//digitalWrite(Z_ENABLE_PIN, HIGH);

	//figure out our deltas
	max_delta = max(delta_steps.x, delta_steps.y);
	max_delta = max(delta_steps.z, max_delta);

	//init stuff.
	long x_counter = -max_delta / 2;
	long y_counter = -max_delta / 2;
	long z_counter = -max_delta / 2;

	//our step flags
	bool x_can_step = 0;
	bool y_can_step = 0;
	bool z_can_step = 0;

	//do our DDA line!
	do {

		x_can_step = canXStep();
		y_can_step = canYStep();
		z_can_step = canZStep();

		if (x_can_step) {
			x_counter += delta_steps.x;

			if (x_counter > 0) {
				do_step(X_STEP_PIN);
				x_counter -= max_delta;

				if (x_direction) {
					current_steps.x++;
				} else {
					current_steps.x--;
				}
			}
		}

		if (y_can_step) {
			y_counter += delta_steps.y;

			if (y_counter > 0) {
				do_step(Y_STEP_PIN);
				y_counter -= max_delta;

				if (y_direction)
					current_steps.y++;
				else
					current_steps.y--;
			}

		}

		if (z_can_step) {
			z_counter += delta_steps.z;
			if (z_counter > 0) {
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
	} while (x_can_step || y_can_step || z_can_step);

	//set our points to be the same
	//current_units.x = target_units.x;
	//current_units.y = target_units.y;
	//current_units.z = target_units.z;
	calculate_deltas();
}

void moveAlongCurve(double cx, double cy, double cz, double fx, double fy,
		double fz, bool clockwise) {
	float angleA, angleB, angle, radius, length, aX, aY, bX, bY;

	aX = (getUnitsX() - cx);
	aY = (getUnitsY() - cy);
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
	if (angleB <= angleA)
		angleB += 2 * M_PI;
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

bool can_step(int min_pin, int max_pin, long current, long target,
		int direction) {
	//stop us if we're on target
	if (target == current) {
		return false;
	}
	//stop us if we're at home and still going
	if (read_switch(min_pin) && !direction) {
		//Serial.println(min_pin);
		//	Serial.println(read_switch(min_pin) );
		//	Serial.println(direction) ;
		//Serial.println("hit minimum pin");
		return false;
	}
	//stop us if we're at max and still going
	if (read_switch(max_pin) && direction) {
		//Serial.println(min_pin);
		//Serial.println(read_switch(min_pin) );
		//Serial.println(direction) ;
		//Serial.println("hit maximum pin");
		return false;
	}
	//default to being able to step
	return true;
}

void do_step(int step_pin) {
	digitalWrite(step_pin, HIGH);
	digitalWrite(step_pin, LOW);
	delayMicroseconds(5);
}

bool read_switch(int pin) {
	return digitalRead(pin) ^ SENSORS_INVERTING;
}

bool canXStep() {
	return can_step(X_MIN_PIN, X_MAX_PIN, current_steps.x, target_steps.x,
			x_direction);
}

bool canYStep() {
	return can_step(Y_MIN_PIN, Y_MAX_PIN, current_steps.y, target_steps.y,
			y_direction);
}

bool canZStep() {
	return can_step(Z_MIN_PIN, Z_MAX_PIN, current_steps.z, target_steps.z,
			z_direction);
}

// ********************************
// converts from mm or inches to steps of the stepper motor
long to_steps(double steps_per_unit, double units) {
	return steps_per_unit * units;
}

void set_target(double x, double y, double z) {
	target_steps.x = to_steps(xStepsPerUnit, x);
	target_steps.y = to_steps(yStepsPerUnit, y);
	target_steps.z = to_steps(zStepsPerUnit, z);

	calculate_deltas();
}

void setPosition(double x, double y, double z) {
	current_steps.x = to_steps(xStepsPerUnit, x);
	current_steps.y = to_steps(yStepsPerUnit, y);
	current_steps.z = to_steps(zStepsPerUnit, z);

	calculate_deltas();
}

void calculate_deltas() {
	delta_steps.x = abs(target_steps.x - current_steps.x);
	delta_steps.y = abs(target_steps.y - current_steps.y);
	delta_steps.z = abs(target_steps.z - current_steps.z);

	setDirection();
}
void setDirection() {
//what is our direction
	setXDirection(target_steps.x > current_steps.x);
	setYDirection(target_steps.y > current_steps.y);
	setZDirection(target_steps.z > current_steps.z);
}

void setXDirection(int dir) {
	x_direction = dir;
	digitalWrite(X_DIR_PIN, dir ^ X_INVERT);
}

void setYDirection(int dir) {
	y_direction = dir;
	digitalWrite(Y_DIR_PIN, dir ^ Y_INVERT);
}

void setZDirection(int dir) {
	z_direction = dir;
	digitalWrite(Z_DIR_PIN, dir ^ Z_INVERT);
}

void setFeedRate(double feedRate) {
	myFeedRateDelay = calculate_feedrate_delay(feedRate);

}

void setMaxFeedRate() {
	myFeedRateDelay = getMinDelay();
}

void delaySteppers(long feedRateDelay) {
	long milliDelay = 0;
	if (feedRateDelay >= 16383) {
		milliDelay = feedRateDelay / 1000;
	}
	//	Serial.print("feedRateDelay: ");
	//	Serial.println(feedRateDelay);
	if (milliDelay > 0)
		delay(milliDelay);
	else
		delayMicroseconds(feedRateDelay);
}

long calculate_feedrate_delay(double feedrate) {
	// feedrate is in (units)/minute
	// feed rate is speed it takes to go 1 unit of distance (D/T)
	// feedRateDelay is how long to wait between steps (T/S)
	// (D/S) is distance per step
	// So conversion is 1/(D/T) *(D/S) = (T/S)
	// or feedRateDelay = 1/feedRate * 1/stepPerUnit
	//  just use zsteps for now
	// This really should use the hypotonuse but doesn't need to be that acurate yet
	if (feedrate == 0)
		return getMinDelay();
	double delay = 1.0 / to_steps(zStepsPerUnit, feedrate);
	delay = delay * 60 * 1000000; // convert from minutes to microseconds
	Serial.print("delay: ");
	Serial.println(delay);
	if (delay < getMinDelay())
		delay = getMinDelay();
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

long getMinDelay() {
	return MINIMUMSTEPPERDELAY;
}

void setInches() {
	xStepsPerUnit = X_STEPS_PER_INCH;
	yStepsPerUnit = Y_STEPS_PER_INCH;
	zStepsPerUnit = Z_STEPS_PER_INCH;
	curve_section = CURVE_SECTION_INCHES;
	calculate_deltas();
}

void setMillimeters() {
	xStepsPerUnit = X_STEPS_PER_MM;
	yStepsPerUnit = Y_STEPS_PER_MM;
	zStepsPerUnit = Z_STEPS_PER_MM;
	curve_section = CURVE_SECTION_MM;
	calculate_deltas();
}

void disable_steppers() {
	//enable our steppers
	//digitalWrite(X_ENABLE_PIN, LOW);
	//digitalWrite(Y_ENABLE_PIN, LOW);
//	digitalWrite(Z_ENABLE_PIN, LOW);
}

void goToZMax() {
	setZDirection(1);
	println("Waiting for ZMax");
	while (!digitalRead(Z_MAX_PIN)) {
		do_step(Z_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}
	goTo(getUnitsX(), getUnitsY(), Z_RESET_LOCATION);
	setPosition(getUnitsX(), getUnitsY(), Z_RESET_LOCATION);
	println("Z finished");
}
void goToZMin() {
	setZDirection(0);
	println("Waiting for ZMin");
	while (!digitalRead(Z_MIN_PIN)) {
		do_step(Z_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}
	goTo(getUnitsX(), getUnitsY(), 0);
	setPosition(getUnitsX(), getUnitsY(), Z_TOUCH_OFF_LOCATION);
	println("Z finished");
}
void goToYMin() {
	setYDirection(0);
	println("Waiting for YMin");
	while (!digitalRead(Y_MIN_PIN)) {
		do_step(Y_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}
	goTo(getUnitsX(), Y_RESET_LOCATION, getUnitsZ());
	setPosition(getUnitsX(), Y_RESET_LOCATION, getUnitsZ());
	println("Y finished");
}

void goToXMin() {
	setXDirection(0);
	println("Waiting for XMin");
	while (!digitalRead(X_MIN_PIN)) {
		do_step(X_STEP_PIN);
		delayMicroseconds(MINIMUMSTEPPERDELAY);
	}
	goTo(X_RESET_LOCATION, getUnitsY(), getUnitsZ());
	setPosition(X_RESET_LOCATION, getUnitsY(), getUnitsZ());
	println("X finished");

}

void goToTouchOff() {
	goTo(X_TOUCH_OFF_LOCATION, Y_TOUCH_OFF_LOCATION, Z_RESET_LOCATION);

	goToZMin();
	setPosition(X_TOUCH_OFF_LOCATION, Y_TOUCH_OFF_LOCATION,
			Z_TOUCH_OFF_LOCATION);
	goTo(X_TOUCH_OFF_LOCATION, Y_TOUCH_OFF_LOCATION, Z_TOUCH_OFF_LOCATION + 1);
}

void resetLocation() {
	goToZMax(); // go to max height to keep bit out of the way
	goToYMin();
	goToXMin();
}

