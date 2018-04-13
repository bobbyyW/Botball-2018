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
#define ARM_DOWN 1671
#define ARM 2

#define CLAW 1
#define CLAW_CLOSE 288

#define MOTOR 0
#define MOTOR_DOWN 70

//NOTFOSHO
#define openClaw 403
#define ARM_UP 100
#define ARM_TRAM 1650
#define CLAW_MID 1000
#define CLAW_OPEN 760


int rf;
int r;
int l;
int lf;

