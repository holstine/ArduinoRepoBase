#include "LCDOutput.h"



void println(char * string){
	clearLCD();
	lcdGoTo(0);
	Serial.println(string);
}

void println(double string){
	clearLCD();
	lcdGoTo(0);
	Serial.println(string);
}

void println(long string){
	clearLCD();
	lcdGoTo(0);
	Serial.println(string);
}

void print(char * string){
	Serial.print(string);
}

void print(double string){
	Serial.print(string);
}

void print(long string){
	Serial.print(string);
}

void resetLCD() {
//	Serial.print(0x07, BYTE);
//	Serial.print(18, BYTE);
}

void clearLCD()
{
//	Serial.print(0xFE, BYTE);
//	Serial.print(0x01, BYTE);
}

void print(){
	printX();
	printY();
	printZ();
}
//
//void printZ(){
//	print("z  ");
//	print(getUnitsZ());
////	print("s  ");
////	print(current_steps.z);
////	print("  t  ");
////	println(target_steps.z);
//}
//void printY(){
//	print("y  ");
//	print(getUnitsY());
////	print("s  ");
////	print(current_steps.y);
////	print("  t  ");
////	println(target_steps.y);
//}
//void printX(){
//	print("x  ");
//	print(getUnitsX());
////	print("s  ");
////	print(current_steps.x);
////	print("  t  ");
////	println(target_steps.x);
//}

void lcdGoTo(int position)
{ //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
//	if (position<16){ Serial.print(0xFE, BYTE); //command flag
//		Serial.print((position+128), BYTE); //position
//	}else if (position<32){Serial.print(0xFE, BYTE); //command flag
//		Serial.print((position+48+128), BYTE); //position
//	} else { lcdGoTo(0); }
}
