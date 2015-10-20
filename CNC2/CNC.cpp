// Do not remove the include below
#include "CNC.h"
#include "init.h"
#include "stepper_control.h"
#include "process_string.h"

// Arduino G-code Interpreter
// redun by  Michael Holstine
// v1.0 by Mike Ellery - initial software (mellery@gmail.com)
// v1.1 by Zach Hoeken - cleaned up and did lots of tweaks (hoeken@gmail.com)
// v1.2 by Chris Meighan - cleanup / G2&G3 support (cmeighan@gmail.com)
// v1.3 by Zach Hoeken - added thermocouple support and multi-sample temp readings. (hoeken@gmail.com)


#include <SD.h>

//our command string


char foo[COMMAND_SIZE];
int serial_count;
int no_data = 0;


void setup(){
clearLCD();
	Serial.begin(9600);
	println("start");
//	testSDCard();
	if(!initSDCard()) return;

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
	Serial.print("processed: " );
	Serial.println(linesProcessed);
}

int initSDCard(){

Serial.print("Initializing SD card...");
	pinMode(8, OUTPUT);

//	if (!SD.begin(4)) {
//		Serial.println("SD initialization failed!");
//		return 0;
//	}
	//  testSDCard();
	Serial.println("initialization done.");
	return 1;
}


// once gcode file is read then the rest can be done by serial terminal if needed
void loop()
{	char c;
	//keep it hot!
	//	extruder_manage_temperature();
	//read in characters if we got them.
	if (Serial.available() > 0)
	{
		c = Serial.read();
		no_data = 0;
		//newlines are ends of commands.
		if (c != '\n')
		{
			foo[serial_count] = c;
			serial_count++;
		}
	}
	//mark no data.
	else
	{
		no_data++;
//		delayMicroseconds(100);
	}
	//if theres a pause or we got a real command, do it
	if (serial_count && (c == '\n' || no_data > 100))
	{
		//process our command!
		process_string(foo, serial_count);

		//clear command.
		init_process_string();
	}
	//no data?  turn off steppers
	if (no_data > 1000)
	disable_steppers();
}
void testSDCard(){
//	int linesProcessed = 0;
//	File myFile = SD.open(GFILENAME);
//	if (myFile) {
//		Serial.println(GFILENAME);
//
//		// read from the file until there's nothing else in it:
//		while (myFile.available()) {
//			linesProcessed ++;
//			Serial.write(myFile.read());
//			if(linesProcessed > 1000) break;
//		}
//		// close the file:
//		myFile.close();
//	} else {
//		// if the file didn't open, print an error:
//		Serial.println("error opening test.txt");
//	}
}
void getFile(){



}
int processGCodeFile(char* filename){
	int linesProcessed = 0;
	char  gline[COMMAND_SIZE];

//	if (!SD.exists(GFILENAME)){
//		Serial.print("error opening ");
//		Serial.println(GFILENAME);
//		return 0;
//	}
//	File file  = SD.open(filename);
//	if (file) {
//		Serial.println(GFILENAME);
//	}

	// read from the file until there's nothing else in it:
//	while (file.available()) {
//		linesProcessed ++;
//		int cmdSize = readGLine(file, gline);
//		println(gline);
//		process_string(gline, cmdSize);
//
//	}
	return linesProcessed;
}

//int readGLine(File file, char * gline){
//	char c;
//	int charcount =0;
//	while(charcount < COMMAND_SIZE){
//		c= file.read();
//		if (c == '\n'){
//			gline[charcount] = '\0';
//			return charcount;
//		}else{
//			gline[charcount] = c;
//			charcount++;
//		}
//	}
//
//}



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
