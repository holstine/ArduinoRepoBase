// Do not remove the include below
#include "CNC4.h"

#include "GcodeProcessor.h"
#include "CNCMachine.h"
#include "FileReader.h"

//The setup function is called once at startup of the sketch
void setup() {
	CNCMachine * m = new CNCMachine();
	GcodeProcessor * processor = new GcodeProcessor(m);
	FileReader * f = new FileReader();

	m->init();
	char * filen = "GCode.txt";
	f->processGCodeFile(processor, filen);
}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
}

