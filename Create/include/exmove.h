///////////////////////////////////////////////////////////////
// exmove.c                                                  //
// Created by Zachary Mayhew                                 //
// For use by botball team 17-0510                           //
// Use for basic functions                                   //
///////////////////////////////////////////////////////////////

#ifndef EXMOVE_H
#define EXMOVE_H

#define LEFT 0
#define RIGHT 1

#define PI 3.141592f

// distance between the two wheels
#define DIAMETER 250.0f
#define RADIUS (250.0f/2.0f)
#define CIRCUMFERENCE DIAMETER*PI

#define ARM_SERVO 1
#define CLAW_SERVO 0

#define CLAW_CLOSED 800
#define CLAW_OPEN 450

#define ARM_DOWN 2000
#define ARM_UP 200
#define ARM_FLAT 1000

#define SPEED 100
#define HIGH_SPEED 200

/**
 * @author Arjun
 */
#define POS_START_X 400
#define POS_START_Y 170
#define POS_COW_X 750
#define POS_COW_Y 2070
#define POS_HAY1_X 1050
#define POS_HAY1_Y 1920
#define POS_HAY2_X 1050
#define POS_HAY2_Y 2070
#define POS_HAY3_X 1050
#define POS_HAY3_Y 2220

/**
 * @author Bobby
 */
#define ARM_X 250
#define ARM_Y 110
#define BACK_Y 130


/**
 * Structure for robot position
 */
typedef struct {
	int x;
	int y;
	int rotation;
} RobotPos;

/**
 * Initializes the library
 * @param x        starting x pos
 * @param y        starting y pos
 * @param rotation starting rotation
 */
void initEx(int x, int y, int rotation);

void slowServo(int servo, int goal, int milliseconds);

/**
 * Sets the position of the claw
 * @param v position
 * @author Zachary Mayhew
 */
void claw(int v);

/**
 * Sets the position of the arm
 * @param v position
 * @author Zachary Mayhew
 */
void arm(int v);

void pick();

void drop();

void pickUpObjectA(int wide, int depth);

/**
 * Picks up an object such as hay bale and puts it in the container
 * @author Zachary Mayhew
 */
void pickUpObject();

/**
 * Moves straight a distance
 * @param mm    distance to be moved
 * @param speed speed at which to move
 * @author Zachary Mayhew
 */
void straight_distance(int mm, int speed);

/**
 * Reverse a certain distance
 * @param mm    Distance to be move
 * @param speed speed to move
 * @author Zachary Mayhew
 */
void reverse_distance(int mm, int speed);

/**
 * Rotates the entire robot to a position
 * @param degrees   angle to move
 * @param direction direction (left or right)
 * @param speed     speed to move
 * @author Bobby Wang
 */

/**
 * FOOOLS ASLKDFJLSKDFJLSKADFJLK S
 * STOP USING DRIVE_STRAIGHT
 * USE THAT THING THAT U USE
 *CREATE_DRIVE_DIRECT [Not in caps]
 */

void rotate(float degrees, int direction, int speed);

/**
 * Creates a new RobotPos structure with starting x and y values
 * @param  x Starting x pos
 * @param  y Starting y pos
 * @return   new robot pos structure
 */
RobotPos newRobotPos(int x, int y, int rotation);

/**
 * Returns the current position of the robot
 * @return the current position of the robot
 */
RobotPos getRobotPos();

/**
 * Sets the postition of the robot
 * NOTE THIS WONT TAKE THE ROBOT TO THIS LOCATION
 * @param pos position of the robot
 */
void setRobotPos(RobotPos pos);


#endif
