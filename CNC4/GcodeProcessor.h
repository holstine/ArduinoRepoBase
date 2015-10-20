/*
 * process_string.h
 *
 *  Created on: Jun 23, 2012
 *      Author: Michael
 */

#ifndef PROCESS_STRING_H_
#define PROCESS_STRING_H_

// our point structure to make things nice.

#include "CNCMachine.h"
#include "arduino.h"

class GcodeProcessor {
//our feedrate variables.


	 double nominalFeedRate;
	 bool abs_mode;
	 Point centr;
	 CNCMachine * machine;

public:
	GcodeProcessor( CNCMachine * m){setMachine(m);}


	inline CNCMachine * getMachine() {
		return machine;
	}
	inline void setMachine(CNCMachine * m) {
		machine = m;
	}
//init our string processing
	void init_process_string(CNCMachine * ma);

//Read the string and execute instructions
	 void process_string(char instruction[]);

//look for the number that appears after the char key and return it
	 double search_string(char key, char instruction[]);
//look for the command if it exists.
	 bool has_command(char key, char instruction[]);

};
#endif /* PROCESS_STRING_H_ */
