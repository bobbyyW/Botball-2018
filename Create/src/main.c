///////////////////////////////////////////////////////////////
// main.c                             //
// For use by botball team 17-0510                           //
///////////////////////////////////////////////////////////////

#include <kipr/botball.h>
#include "exmove.h"
#include "initialDrive.h"
#include "farmHayBales.h"
#include "blueCow.h"

//#define HAY_TEST // NOTE MAKE SURE THAT IF YOU ARE TESTING SOMETHING OTHER THAN HAY TO COMMENT THIS OUT

/**
 * Initialise create and servos
 */
void init() {
	printf("Conecting to Create\n");
	// TODO Add light activate
	create_connect();
    printf("msleep\n");
    //msleep(1500);
    printf("start\n");
    create_full();
	printf("connected\n");
	// light here
    set_servo_position(ARM_SERVO, ARM_UP);
    set_servo_position(CLAW_SERVO, CLAW_CLOSED);    //set starting values

  enable_servo(ARM_SERVO);
	enable_servo(CLAW_SERVO);


	initEx(POS_START_X, POS_START_Y, 0);
    //arm(ARM_UP);

}


/**
 * Deinitialize create and servos
 */
void dinit() {
	//disable_servo(ARM_SERVO);
	//disable_servo(CLAW_SERVO);
    disable_servos();   //Disable all servos - make sure you are not DQed
	create_disconnect();
	printf("Done!\n");
}

int main() {
  
  	printf("init\n");
	init();
  
    wait_for_light(0);
    shut_down_in(119);
    create_start();

#ifndef HAY_TEST
	printf("Exec: initDrive\n");
	initialDrive();
	printf("Exec: blueCow\n");
	blueCow();
#endif
	printf("Exec: hay\n");
	farmHayBales();


	printf("dinit\n");
	dinit();
	return 0;
}

