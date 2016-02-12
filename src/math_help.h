/*
 * RobotVikings
 * math.h
 * 12/6/15
 * Declares math functions to help with whatever we may need them for.
 */

#ifndef _MATH_HELP_H_
#define _MATH_HELP_H_

namespace math_help{
 /*
  * Q_rsqrt
  * Accepts a float
  * Returns a float
  * Quickly and efficiently calculates x^(-1/2), where x is any floating point number.
  */
 float Q_rsqrt(float);

 /*
  * cos
  * Accepts a float and an optional int
  * Returns a float
  * Calculates the cosine of a number as many times as is specified
  */
 float cos(float,int);

 /*
  * sin
  * Accepts a float and an optional int
  * Returns a float
  * Calculates the sine of a number as many times as is specified
  */
 float sin(float,int);

}

#endif
