#ifndef MINIFIED
#ifdef __GNUC__
#include "kipr/botball.h"
#else
#include <kipr/botball.h>
#endif
#include "exmove.h"
#include "createDrive.h"
#endif

RobotPos currentPos;

void initEx(int x, int y, int rotation) {
	currentPos = newRobotPos(x, y, rotation);
}

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

void claw(int v) {
	// slowServo(CLAW_SERVO, v, speed);
    printf("claw %d\n", v);
  	set_servo_position(CLAW_SERVO, v);
  	msleep(500);
}

void arm(int v) {
    printf("arm %d\n", v);
	set_servo_position(ARM_SERVO, v);
    msleep(1000);
}

void pickUpObject(int wide) {
	pickUpObjectA(wide, 0);
}

void pickUpObjectA(int wide, int depth) {
  claw(CLAW_OPEN - wide);
  	slowServo(ARM_SERVO, ARM_DOWN, 1000);
  	msleep(300);
	slowServo(CLAW_SERVO, CLAW_CLOSED, 1000);
	slowServo(ARM_SERVO, ARM_UP, 1000);
  	msleep(1000);	//arm shakes
    claw(CLAW_OPEN - wide);
  	msleep(500);
}

void pick() {
    arm(ARM_DOWN);
    claw(CLAW_CLOSED);
    arm(ARM_UP);
}

void drop() {
    arm(ARM_DOWN);
    claw(CLAW_OPEN);
}

// go straight a certain distance TODO Make it more accurate
void straight_distance(int mm, int speed) {
	currentPos.x += mm * sin(currentPos.rotation);
	currentPos.y += mm * cos(currentPos.rotation);
    printf("create_drive_straight %d\n", speed);
	create_drive_direct(speed * 1.1, speed * 0.9);
    printf("msleep %d\n", mm * 1000 / speed);
	msleep(mm * 1000 / speed);
    printf("create_stop\n");
	create_stop();
}

void reverse_distance(int mm, int speed) {
	currentPos.x += mm * sin(currentPos.rotation);
	currentPos.y += mm * cos(currentPos.rotation);
    //printf("create_drive_straight %d\n", speed);
	create_drive_straight(-speed);
    //printf("msleep %d\n", (mm/speed) * 1000);
	msleep((mm/speed) * 1000);
    //printf("create_stop\n");
	create_stop();
}

// Rotate by a given degree, in the given direction, at the given speed.
// todo: make it more accurate
void rotate(float degrees, int direction, int speed) {
    float distance = ((degrees/360) * CIRCUMFERENCE);
    if (direction == LEFT) {
			currentPos.rotation-=degrees;
			create_spin_CCW(speed);
    } else {
			currentPos.rotation+=degrees;
			create_spin_CW(speed);
    }
		msleep((distance/speed)*1000);
		create_stop();
}

RobotPos newRobotPos(int x, int y, int rotation) {
	RobotPos pos;
	pos.x = x;
	pos.y = y;
	pos.rotation = rotation;
	return pos;
}

RobotPos getRobotPos() {
	return currentPos;
}

void updateRobotPos(int x, int y) {
    currentPos.x += x;
    currentPos.y += y;
}

void setRobotPos(RobotPos pos) {
	currentPos = pos;
}
