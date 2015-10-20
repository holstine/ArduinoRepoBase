// Do not remove the include below
#include "CNC3.h"

#include "GcodeProcessor.h"
#include "CNCMachine.h"
#include "FileReader.h"

CNCMachine m;
GcodeProcessor processor(m);
FileReader f;
//The setup function is called once at startup of the sketch
void setup() {

	m.init();
	char * filen;
	f.loadFile(filen);

}

// The loop function is called in an endless loop
void loop() {
//Add your repeated code here
}
int processGCodeFile(FileReader f, char* filename) {


	//	 read from the file until there's nothing else in it:
	while (f.isAvailable()) {
		 char * gline = f.readGLine();
		//		println(gline);
		processor.process_string(gline);

	}


}
