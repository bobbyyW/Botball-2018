#include <stdio.h>
#ifndef MINIFIED
#ifdef __GNUC__
#include "kipr/botball.h"
#else
#include <kipr/botball.h>
#endif
#endif

#define get_high_byte2(a) (((a)>>8)&255)
#define get_low_byte2(a) ((a)&255)
//FOSHO
#define ARM_DOWN 2047
#define ARM 2

#define CLAW 1
#define CLAW_CLOSE 221

#define MOTOR 0
#define MOTOR_DOWN 70
//motor down pos 216

#define CLAW_OPEN 1397
#define BOTGUY_CLOSE 0
#define BOTGUY_ARM_DOWN 

#define ARM_UP 0

//NOTFOSHO

#define ARM_TRAM 1650
#define CLAW_MID 1000



int rf;
int r;
int l;
int lf;

