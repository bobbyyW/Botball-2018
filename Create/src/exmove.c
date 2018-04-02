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


//HOWARD's ARM MOVEMENT STUFF

void setup() {
  clear_motor_position_counter(MOTOR_ARM);  //position at base, anchored at 0

  clawOpen();

}


void botguyClose() {
  set_servo_position(CLAW, BOTGUY_CLOSE);
}

void clawOpen() {
  set_servo_position(CLAW, CLAW_OPEN);
}


void armUp(int distance, int power) {
  distance = distance * 100;
  
  int initialPosition = get_motor_position_counter(MOTOR_ARM);
  printf("Initial Position: %d", initialPosition);
  power = -1 * power;
  
  motor(MOTOR_ARM, power);
  int difference = abs(gmpc(MOTOR_ARM) - initialPosition);
  while(difference < distance) {
    printf("Position: %d\n", gmpc(MOTOR_ARM));
    msleep(100);
    difference = abs(gmpc(MOTOR_ARM) - initialPosition);
  }
  motor(MOTOR_ARM, 0);
  
}

