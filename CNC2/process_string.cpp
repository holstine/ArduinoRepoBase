// our point structure to make things nice.
#include "process_string.h"
#include "Stepper_state.h"
#include "init.h"
//our feedrate variables.

//init our string processing
void init_process_string()
{
  //init our command
  for (byte i=0; i<COMMAND_SIZE; i++)
    foo[i] = 0;
  serial_count = 0;

}

//Read the string and execute instructions
void process_string(char instruction[], int size)
{ 
  //the character / means delete block... used for comments and stuff.
  if (instruction[0] == '/' 
	|| instruction[0] == ';'
	|| instruction[0] == '#'){
    return; 
  }

FloatPoint target;
FloatPoint currentPosition;
currentPosition.x = getUnitsX();
currentPosition.y = getUnitsY();
currentPosition.z = getUnitsZ();


byte code = 0;

   //Get Target
    
		target.x = currentPosition.x ;
		target.y = currentPosition.y ;
		target.z = currentPosition.z ; 
        if (has_command('X', instruction, size)) target.x = search_string('X', instruction, size);
        if (has_command('Y', instruction, size)) target.y = search_string('Y', instruction, size);
        if (has_command('Z', instruction, size)) target.z = search_string('Z', instruction, size);
     
	 if(!abs_mode){
        target.x = currentPosition.x + search_string('X', instruction, size);
        target.y =  currentPosition.y + search_string('Y', instruction, size);;
        target.z =  currentPosition.z + search_string('X', instruction, size);;
      }
	//set our target.
      set_target(target.x, target.y, target.z);
  
	double feedrate = search_string('F', instruction, size);
    if (feedrate > 0)  nominalFeedRate = feedrate;
  
  
  
  // handle no G code but has Coordinates remember the last feed rate
  if( ( has_command('X', instruction, size) ||
		has_command('Y', instruction, size) ||
		has_command('Z', instruction, size))&& 
		! has_command('G', instruction, size)){
		//	setFeedRate(nominalFeedRate);
			goTo(target.x, target.y, target.z);

	}		
  
  
  if (    has_command('G', instruction, size)     )
  {
    //which one?
    code = (int)search_string('G', instruction, size);
    switch (code)
    {
      //Rapid Positioning
    case 0:
		setMaxFeedRate();
		goTo(target.x, target.y, target.z);
	break;
	
	//Linear Interpolation
    case 1:
		setFeedRate(nominalFeedRate);
		goTo(target.x, target.y, target.z);
      break;


      //Clockwise arc
    case 2:
      //Counterclockwise arc
    case 3:
      FloatPoint cent;

      // Centre coordinates are always relative
      cent.x = search_string('I', instruction, size) + currentPosition.x;
      cent.y = search_string('J', instruction, size) + currentPosition.y;
      cent.z = target.z; 
      bool clockwise;
	 clockwise	  = (code==2);

      moveAlongCurve( cent.x, cent.y, cent.z,  target.x, target.y, target.z, clockwise); 
      break;

    case 4:
      delay(1000*(int)search_string('P', instruction, size));
      break;

      //Inches for Units
    case 20:
      setInches(); 
      break;

      //mm for Units
    case 21:
      setMillimeters(); 
      break;

      //go home.
    case 28:
      goTo(0.0, 0.0, 0.0); 
      break;

      //go home via an intermediate point.
    case 30:
      setMaxFeedRate();
		goTo(target.x, target.y, target.z);
      //go home.
      goTo(0.0, 0.0, 0.0); 
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
      setPosition(0.0, 0.0, 0.0);
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
      Serial.print("huh? G");
      Serial.println(code,DEC);
    }
  }

  if (has_command('F', instruction, size))
  {
		double rate = search_string('F', instruction, size);
		setFeedRate(rate);
		nominalFeedRate = rate;
		
  }
  //find us an m code.
  if (has_command('M', instruction, size))
  {
    code = search_string('M', instruction, size);
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
      Serial.print("Huh? M");
      Serial.println(code);
    }		
  }

  //tell our host we're done.
  Serial.println("ok");
  //	Serial.println(line, DEC);
}

//look for the number that appears after the char key and return it
double search_string(char key, char instruction[], int string_size)
{
  char temp[10] = "";

  for (byte i=0; i<string_size; i++)
  {
    if (instruction[i] == key)
    {
      i++;      
      int k = 0;
      while (i < string_size && k < 10)
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
bool has_command(char key, char instruction[], int string_size)
{
  for (byte i=0; i<string_size; i++)
  {
    if (instruction[i] == key)
      return true;
  }

  return false;
}




