#ifndef MINIFIED
#ifdef __GNUC__
#include "kipr/botball.h"
#else
#include <kipr/botball.h>
#endif
#endif

#define get_high_byte2(a) (((a)>>8)&255)
#define get_low_byte2(a) ((a)&255)

#define openClaw 403

int rf;
int r;
int l;
int lf;

