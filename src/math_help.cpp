/*
 * RobotVikings
 * math.cpp
 * 12/6/15
 * Defines math functions to help with whatever we may need them for.
 */

#include <math.h>
#include "math_help.h"

static int calc_denom(int exp){
    int d = 1;
    for(int i=exp;i>1;i--)
        d*=i;
    return d;
}

// Copied from https://en.wikipedia.org/wiki/Fast_inverse_square_root
float math_help::Q_rsqrt(float number){
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y  = number;
    i  = * ( long * ) &y;                       // evil floating point bit level hacking
    i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
    y  = * ( float * ) &i;
    y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//  y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

float math_help::cos(float x, int n){
    float total=1;
    int exp = 2;
    int denom = 1;
    int sign = 1;
    for(int i=0; i<n;i++){
        denom = calc_denom(exp);
        total += pow(x,exp)/denom*sign;
        sign*=-1;
        exp+=2;
    }
    return total;
}

float math_help::sin(float x, int n){
    float total=x;
    int exp = 3;
    int denom = 1;
    int sign=1;
    for(int i=0; i<n;i++){
        denom = calc_denom(exp);
        total+= pow(x,exp)/denom*sign;
        sign*=-1;
        exp+=2;
    }
    return total;
}

float math_help::tan(float x, int n){ return sin(x,n)/cos(x,n); }

float math_help::asin(float x, int n){ return 1/sin(x,n); }
float math_help::acos(float x, int n){ return 1/cos(x,n); }
float math_help::atan(float x, int n){ return cos(x,n)/sin(x,n); }

