/*
 * SerialOutput.h
 *
 *  Created on: Jun 25, 2012
 *      Author: Michael
 */

#ifndef SERIALOUTPUT_H_
#define SERIALOUTPUT_H_

#include <Arduino.h>
void println(char * string);
void println(double string);
void println(long string);
void print(char * string);
void print(double string);
void print(long string);
void resetLCD();
void clearLCD();
void print();
void printZ();
void printY();
void printX();
void lcdGoTo(int position);


#endif /* SERIALOUTPUT_H_ */
