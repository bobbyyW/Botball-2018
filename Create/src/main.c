///////////////////////////////////////////////////////////////
// main.c                             //
// For use by botball team 18-0510                           //
///////////////////////////////////////////////////////////////

#include <kipr/botball.h>
#include "exmove.h"
#include "createDrive.h"
#include "initialDrive.h"

//#define HAY_TEST // NOTE MAKE SURE THAT IF YOU ARE TESTING SOMETHING OTHER THAN HAY TO COMMENT THIS OUT

/**
 * Initialise create and servos
 */
void init() {
	printf("Conecting to Create\n");
	// TODO Add light activate
	create_connect();
    	printf("start\n");
    	create_full();
	printf("connected\n");
	// light here
    	set_servo_position(ARM_SERVO, ARM_UP);
    	set_servo_position(CLAW_SERVO, CLAW_CLOSED);    //set starting values

  	enable_servo(ARM_SERVO);
	enable_servo(CLAW_SERVO);

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
  
    	//wait_for_light(0);
    	//shut_down_in(119);
    	create_start();

	//FUNCTIONS
    
    initialDrive();

	printf("dinit\n");
	dinit();
	return 0;


  
}
