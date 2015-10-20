/*
 * FileReader.h
 *
 *  Created on: Jul 21, 2012
 *      Author: Michael
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "SD.h"
#include "GcodeProcessor.h"
class FileReader {
public:
	FileReader(){};
	virtual ~FileReader(){};
	File myFile;
	char* fileName;
	int maxFileLength;
	bool loadFile(char * fn);
	void testSDCard();
	int linesProcessed;
	bool isAvailable();
	char * readGLine();

	int processGCodeFile(GcodeProcessor * processor,  char* filename) ;


};

#endif /* FILEREADER_H_ */
