// our point structure to make things nice.

//#include "stepper_control.h"
//#include "LCDOutput.h"
//#include "init.h"

#include "GcodeProcessor.h"
#include "Point.h"
#include "CNCMachine.h"
//our feedrate variables.


//init our string processing
void  GcodeProcessor::init_process_string(CNCMachine ma)
{
  //init our command
//  for (byte i=0; i<COMMAND_SIZE; i++)
//    foo[i] = 0;
//  serial_count = 0;
	 setMachine(ma);
	 abs_mode = true;
}

//Read the string and execute instructions
 void GcodeProcessor::process_string(char instruction[])
{ 
  //the character / means delete block... used for comments and stuff.
  if (instruction[0] == '/' 
	|| instruction[0] == ';'
	|| instruction[0] == '#'){
    return; 
  }

//  float  currentPosition[] ={getUnitsX(), getUnitsY(), getUnitsZ() };
Point currentPosition = getMachine().getCurrentPosition();
  Point target ;


int code = 0;

   //Get Target
    
		target.x = currentPosition.x ;
		target.y = currentPosition.y ;
		target.z = currentPosition.z ;
        if (has_command('X', instruction)) target.x = search_string('X', instruction);
        if (has_command('Y', instruction)) target.y = search_string('Y', instruction);
        if (has_command('Z', instruction)) target.z = search_string('Z', instruction);
     
	 if(!abs_mode){
		target.x = currentPosition.x + search_string('X', instruction);
        target.y =  currentPosition.y + search_string('Y', instruction);;
        target.z =  currentPosition.z + search_string('X', instruction);;
      }
	//set our target.
//	 getMachine().set_target(target);
  
	double feedrate = search_string('F', instruction);
    if (feedrate > 0)  nominalFeedRate = feedrate;
  
  
  
  // handle no G code but has Coordinates remember the last feed rate
  if( ( has_command('X', instruction) ||
		has_command('Y', instruction) ||
		has_command('Z', instruction))&&
		! has_command('G', instruction)){
		//	setFeedRate(nominalFeedRate);
	  getMachine().goTo(target);

	}		
  
  
  if (    has_command('G', instruction)     )
  {
    //which one?
    code = (int)search_string('G', instruction);
    switch (code)
    {
      //Rapid Positioning
    case 0:
    	getMachine().setMaxFeedRate();
    	getMachine().goTo(target);
	break;
	
	//Linear Interpolation
    case 1:
    	getMachine().setFeedRate(nominalFeedRate);
    	getMachine().goTo(target);
      break;


      //Clockwise arc
    case 2:
      //Counterclockwise arc
    case 3:


      // Centre coordinates are always relative
      centr.x = search_string('I', instruction) + currentPosition.x;
      centr.y = search_string('J', instruction) + currentPosition.y;
      centr.z = target.z;
      bool clockwise;
	 clockwise	  = (code==2);

	 getMachine().moveAlongCurve( centr,  target, clockwise);
      break;

    case 4:
//      delay(1000*(int)search_string('P', instruction, size));
      break;

      //Inches for Units
    case 20:
    	getMachine().setInches();
      break;

      //mm for Units
    case 21:
    	getMachine().setMillimeters();
      break;

      //go home.
    case 28:
    	getMachine().goToOrigin();
      break;

      //go home via an intermediate point.
    case 30:
    	getMachine().setMaxFeedRate();
    	getMachine().goTo(target);
      //go home.
		getMachine().goToOrigin();
      break;

      //Absolute Positioning
    case 90:
      abs_mode = true; 
      break;

      //Incremental Positioning
    case 91:
	
      abs_mode = false;
      break;

      //Set as home
    case 92:
    	getMachine().setPosition(Point());
      break;

      /*
			//Inverse Time Feed Mode
       			case 93:
       
       			break;  //TODO: add this
       
       			//Feed per Minute Mode
       			case 94:
       
       			break;  //TODO: add this
       */

    default:
    	break;
//      Serial.print("huh? G");
//      Serial.println(code,DEC);
    }
  }

  if (has_command('F', instruction))
  {
		double rate = search_string('F', instruction);
		getMachine().setFeedRate(rate);
		 nominalFeedRate = rate;
		
  }
  //find us an m code.
  if (has_command('M', instruction))
  {
    code = search_string('M', instruction);
    switch (code)
    {
      //TODO: this is a bug because search_string returns 0.  gotta fix that.
    case 0:
      true;
      break;
      /*
			case 0:
       				//todo: stop program
       			break;
       
       			case 1:
       				//todo: optional stop
       			break;
       
       			case 2:
       				//todo: program end
       			break;
       	*/
      //set max extruder speed, 0-255 PWM
//    case 100:
//      extruder_speed = (int)(search_string('P', instruction, size));
//      break;
//
//      //turn extruder on, forward
//    case 101:
//      extruder_set_direction(1);
//      extruder_set_speed(extruder_speed);
//      break;
//
//      //turn extruder on, reverse
//    case 102:
//      extruder_set_direction(0);
//      extruder_set_speed(extruder_speed);
//      break;
//
//      //turn extruder off
//    case 103:
//      extruder_set_speed(0);
//      break;
//
//      //custom code for temperature control
//    case 104:
//      extruder_set_temperature((int)search_string('P', instruction, size));
//
//      //warmup if we're too cold.
//      while (extruder_get_temperature() < extruder_target_celsius)
//      {
//        extruder_manage_temperature();
//        Serial.print("T:");
//        Serial.println(extruder_get_temperature());
//        delay(1000);
//      }
//
//      break;
//
//      //custom code for temperature reading
//    case 105:
//      Serial.print("T:");
//      Serial.println(extruder_get_temperature());
//      break;
//
//      //turn fan on
//    case 106:
//      extruder_set_cooler(255);
//      break;
//
//      //turn fan off
//    case 107:
//      extruder_set_cooler(0);
//      break;

    default:
    	break;
//      Serial.print("Huh? M");
//      Serial.println(code);
    }		
  }

  //tell our host we're done.
//  Serial.println("ok");
  //	Serial.println(line, DEC);
}

//look for the number that appears after the char key and return it
double GcodeProcessor::search_string(char key, char instruction[])
{
  char temp[10] = "";

  for (int i=0; i<instruction[i]!='\0'; i++)
  {
    if (instruction[i] == key)
    {
      i++;      
      int k = 0;
      while (instruction[i]!='\0'  && k < 10)
      {
        if (instruction[i] == 0 || instruction[i] == ' ')
          break;

        temp[k] = instruction[i];
        i++;
        k++;
      }
      return strtod(temp, NULL);
    }
  }
	// if no key then return 0
  return 0;
}

//look for the command if it exists.
bool  GcodeProcessor::has_command(char key, char instruction[])
{
  for (int i=0; i<instruction[i]!='\0'; i++)
  {
    if (instruction[i] == key)
      return true;
  }

  return false;
}



