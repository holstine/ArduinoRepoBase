/*
 * FileReader.cpp
 *
 *  Created on: Jul 21, 2012
 *      Author: Michael
 */

#include "FileReader.h"
#include "SD.h"
#include "GcodeProcessor.h"

bool FileReader::loadFile(char * fn) {

		fileName = fn;
		if (!SD.exists(fileName)) {
//			Serial.print("error opening ");
//			Serial.println(fileName);
		}
		myFile = SD.open(fileName);
		if (myFile) {
//			Serial.println(fileName);
		}
		linesProcessed =0;
		return true;
}

void FileReader::testSDCard() {
	int linesProcessed = 0;
	 myFile = SD.open(fileName);
	if (myFile) {
//		Serial.println(fileName);

		// read from the file until there's nothing else in it:
		while (myFile.available()) {
			linesProcessed ++;
//			Serial.write(myFile.read());
			if(linesProcessed > 1000) break;
		}
		// close the file:
		myFile.close();
	} else {
		// if the file didn't open, print an error:
//		Serial.println("error opening test.txt");
	}
}

bool FileReader::isAvailable(){
	return myFile.available();
}

char *   FileReader::readGLine( ){
	char c;
	char * gline;
	int charcount =0;
	while(charcount < maxFileLength){
		c= myFile.read();
		if (c == '\n'){
			gline[charcount] = '\0';
			return gline;
		}else{
			gline[charcount] = c;
			charcount++;
		}
	}
	linesProcessed ++;
	return gline;
}

int  FileReader::processGCodeFile(GcodeProcessor * processor, char* filename) {
	loadFile(filename);
	//	 read from the file until there's nothing else in it:
	while (isAvailable()) {
		char * gline = readGLine();
		//		println(gline);
		processor->process_string(gline);

	}
}
