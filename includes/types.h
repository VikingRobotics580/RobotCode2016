/*
 * RobotVikings
 * types.h
 * 12/11/15
 * Defines custom types.
 */

#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

typedef unsigned long long uint64;
typedef unsigned long uint32;
typedef unsigned int uint16;
typedef unsigned short uint8;

/*******************************/

typedef const char* cstr;

/*******************************/

#include <map>
#include <string>

class joystick;

typedef std::map<std::string,joystick*> jmap;

/*******************************/

#include "WPILib.h"

typedef std::map<std::string,SpeedController*> talon_map;
typedef std::map<std::string,Servo*> servo_map;
typedef std::map<std::string,AnalogInput*> analogio_map;
typedef std::map<std::string,DigitalInput*> digitalio_map;

#endif

