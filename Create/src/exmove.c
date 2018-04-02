#ifndef MINIFIED
#ifdef __GNUC__
#include "kipr/botball.h"
#else
#include <kipr/botball.h>
#endif
#include "createDrive.h"
#endif



void slowServo(int servo, int goal, int milliseconds) {
    int startPos = get_servo_position(servo);
    int goalRelative = goal - startPos;
    // how far to move the servo every time
    float oneMove = (float)(goalRelative) / (milliseconds / 5.0); // 5 ms delay
    //                      ^-- delta        ^-- number of loops

    float pos;
    for (pos = 0; fabsf(pos) < abs(goalRelative); pos += oneMove) {
        set_servo_position(servo, (int)(pos + startPos));
        msleep(5);
    }
    set_servo_position(servo, goal);
}
