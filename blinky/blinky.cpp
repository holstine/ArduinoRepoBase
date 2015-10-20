// Do not remove the include below
#include "blinky.h"
int ledPin = 13;
boolean ledState = false;
void flash(){
 // Flash the LED on pin 13 just to show that something is happening
  // Also serves as an indication that we're not "stuck" waiting for TWI data
  ledState = !ledState;
  if (ledState) {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }
}

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
}


void loop()
{
	delay(5000);
	flash();
}
