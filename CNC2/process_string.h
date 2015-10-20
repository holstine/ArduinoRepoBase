/*
 * process_string.h
 *
 *  Created on: Jun 23, 2012
 *      Author: Michael
 */

#ifndef PROCESS_STRING_H_
#define PROCESS_STRING_H_

// our point structure to make things nice.


//our feedrate variables.

//init our string processing
void init_process_string();

//Read the string and execute instructions
void process_string(char instruction[], int size);

//look for the number that appears after the char key and return it
double search_string(char key, char instruction[], int string_size);
//look for the command if it exists.
bool has_command(char key, char instruction[], int string_size);







#endif /* PROCESS_STRING_H_ */
