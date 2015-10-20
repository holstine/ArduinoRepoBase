// Do not remove the include below
#include "BluetoothTest.h"


int count =0;
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

	Serial.begin(115200);
}

// The loop function is called in an endless loop
void loop()
{


	Serial.print("Hello, world: ");
	Serial.print(count ++);
	Serial.print("      msg read:" );
	Serial.println(Serial.readString());
	Serial.print("x");
	delay(1000);
	flash();
}

