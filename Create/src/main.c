///////////////////////////////////////////////////////////////
// main.c                             //
// For use by botball team 18-0510                           //
///////////////////////////////////////////////////////////////

#include <kipr/botball.h>
#define ARM 0
#define ARM_DOWN 2000
#define ARM_BOT_DOWN 580
#define BOTGUY_ARM_UP 1450
#define ARM_UP 15
#define ARM_PUT 500
#define ARM_PUTTER 600
#define ARM_TRAM 1650

#define CLAW 1
#define CLAW_CLOSE 100
#define CLAW_OPEN 1471
#define CLAW_MID 1100
#define BOTGUY_CLOSE 219
#define DISC_CLOSE 235

#define MOTOR_ARM 0
#define MOTOR 0
#define MOTOR_MOVE 750
#define MOTOR_DOWN_POS 3600
#define MOTOR_UP -1550
#define MOTOR_ALL -1626

#define ARM_REST -1000
#define CLAW_REST 100
#define WRIST_REST 2000

int black = 1400;//was 1100
int white = 2589;

int rf;
int r;
int l;
int lf;

// Operator position: the higher positioned black ring is on the left hand. the side close to the operator is called
// bottom side. The long black line that extends away from the operator is called vertical line.

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

void initialDrive() {    

#define armDisk 1150
#define armUp 700
#define clawDisk 400
#define clawOpen 1471
#define arm 0
#define claw 1
        
    // move the arm to perpendicular position
    move_to_position(MOTOR,1000,0);
    msleep(100);
    block_motor_done(MOTOR);
    
    // square up on the bottom side
    create_drive_direct(-100,-250);
    msleep(2000);
    white = get_create_lcliff_amt();
    printf("rf: %d\n", get_create_rfcliff_amt());
    printf("squared up\n white : %d\n", white);
    
    // square up on the left side
    create_drive_straight(100);
    msleep(800);
    create_drive_direct(-100,100);
    msleep(1600);
    printf("square");
    
    // move towards the frisbee by moving backward since the arm is facing the back
    create_drive_straight(-100);
    msleep(800);

    // move while both left and right sensors are on white
    // todo: remove the hardcoded 900
     while(get_create_lcliff_amt() > black+900 && get_create_rcliff_amt() > black+900) {
        create_drive_direct(-50, -50);
        msleep(1);
    }

    // move past the first black line
    create_drive_direct(-50,-50);
    msleep(1500);
    
    // move while both left and right sensors are on white
    // todo: remove the hardcoded 900
    while(get_create_lcliff_amt() > black+900 && get_create_rcliff_amt() > black+900) {
        create_drive_direct(-50, -50);
        msleep(1);
    }
    
    // square up on the second black line
    if(get_create_lcliff_amt() > black+900) {
        while(get_create_lcliff_amt() > black+400) {
            create_drive_direct(-25, 5);
        }
    } else {
        while(get_create_rcliff_amt() > black+400) {
            create_drive_direct(5, -25);
        }
    }

    
    create_stop();
    msleep(300);
    
    // Raise arm
    move_to_position(MOTOR,750,400);
    msleep(100);
    block_motor_done(0);
    // Open claw
    // todo: change to slowServo
    set_servo_position(claw, clawOpen+400);
    msleep(300);
    // Move wrist to position
    set_servo_position(arm, armDisk);//SET POSITIONS
    msleep(300);
    
    // Move towards frisbee
    create_drive_direct(-100, -100);
    msleep(1600);//was 1600
    create_stop();
    msleep(1000);
    
    // Close claw
    slowServo(claw, clawDisk, 500);
    msleep(300);
    // Raise wrist
    slowServo(arm, armUp, 1500);
    msleep(300);
    
    // Move while left sensor is on white
    // todo: remove hardcoded 400
    while(get_create_lcliff_amt() > black+400) {
        create_drive_direct(100, 100);
        msleep(1);
    }
    create_stop();
    
    // Move past the black line
    create_drive_direct(100, 100);
    msleep(450);
    // Turn right 90 degree to align with the black line
    create_spin_CW(100);
    msleep(1500);
    
    // Follow vertical line using left front sensor until right sensor is on horizontal black line.
    while(get_create_rcliff_amt() > black + 400) {
    	int x = get_create_lfcliff_amt() - (black+white)/2;
        create_drive_direct(60+x/23, 60-x/23);
        msleep(1);
    }

    create_stop();
    msleep(300);
    
    // Raise arm
    move_to_position(0,750,MOTOR_UP);
    msleep(100);
    block_motor_done(0);
    msleep(300);
    slowServo(ARM,ARM_UP,1000);
    
    // Turn right so that the left front sensor is not on black.
    create_spin_CW(100);
    msleep(1000);
    
    // Square up until the left front sensor is on horizontal black line.
   	while(get_create_lfcliff_amt() > black + 200){
        create_spin_CW(100);
    	msleep(1);
    }
    create_spin_CW(100);
    msleep(125); //DELETE IF NOT NEEDED
    
    // Move towards the tram
    create_drive_straight(-100);
    msleep(750);//more 900 less 750
    create_stop();
    
    // Lower the wrist
    slowServo(ARM,1000,500);
    // Open claw to drop the frisbee into the tram
    slowServo(CLAW, CLAW_MID, 500);
}

void GetBotguy(){
    //start with the back facing botguy
    printf("GetBotguy\n");
    
    // Turn 180 degree
    slowServo(ARM,ARM_UP,500);
    create_drive_direct(100,-100);
    msleep(3200);
    printf("spun");
    create_stop();
    
    // Lower the arm before moving towards the botguy
    // Close claw
    slowServo(claw,CLAW_CLOSE,500);
    // Lower arm
    msleep(300);
    move_to_position(MOTOR_ARM,MOTOR_MOVE,MOTOR_DOWN_POS);
    msleep(300);
    block_motor_done(MOTOR_ARM);
    // Lower wrist
    slowServo(ARM,580,1500);

    // Move towards botguy while both right and left sensors are on white
    while(get_create_lcliff_amt() > black+900 && get_create_rcliff_amt() > black+900) {
        create_drive_direct(-50, -50);
        msleep(1);
    }
    
    // Square up on vertical black line
    // todo: make it a function
    if(get_create_lcliff_amt() > black+900) {
        while(get_create_lcliff_amt() > black+900) {
            create_drive_direct(-50, 5);
        }
    } else {
        while(get_create_rcliff_amt() > black+900) {
            create_drive_direct(5, -50);
        }
    }
        
    // Move into box 
    create_drive_direct(-100,-100);
    msleep(850);
    create_stop();
    
    // Open claw
    slowServo(CLAW,CLAW_MID,1000);
    // Lower wrist
    slowServo(ARM,680,1000);
    // Move towards botguy
    create_drive_straight(-100);
    msleep(1500);
    create_stop();
    // Grab botguy
    slowServo(CLAW,BOTGUY_CLOSE,2000);
    
    // Move back while both left and right sensors are on white
    // todo: make a function
    while(get_create_lcliff_amt() > black+900 && get_create_rcliff_amt() > black+900) {
        create_drive_direct(50,50);
        msleep(1);
    }
    // Square up on vertical line
    if(get_create_lcliff_amt() > black+400) {
        while(get_create_lcliff_amt() > black+900) {
            create_drive_direct(50, -5);
        }
    } else {
        while(get_create_rcliff_amt() > black+400) {
            create_drive_direct(-5, 50);
        }
    }

    // Move back a bit more so that there is room to raise arm
    create_drive_straight(100);
    msleep(1750);
    create_stop();
    printf("got the guy, out of the box");
    msleep(300);
    
    // Raise arm
    move_to_position(MOTOR,MOTOR_MOVE-150,MOTOR_UP);
    msleep(100);
    block_motor_done(MOTOR_ARM);
    printf("finished getting arm into pos to go backwards then drop");
    // Raise wrist
    slowServo(ARM,ARM_UP,1000);
    
    // Turn 180 degree
    create_drive_direct(100,-100);
    msleep(3200);
    
    // Move towards the tram while both left and right sensors are on white
    while(get_create_lcliff_amt() > black+900 && get_create_rcliff_amt() > black+900) {
        create_drive_direct(50,50);
        msleep(1);
    }
    // Square up on vertical line
    if(get_create_lcliff_amt() > black+400) {
        while(get_create_lcliff_amt() > black+900) {
            create_drive_direct(50, -5);
        }
    } else {
        while(get_create_rcliff_amt() > black+400) {
            create_drive_direct(-5, 50);
        }
    }
    
    // Move away from tram slightly
    create_drive_straight(-50);
    msleep(750);
    create_stop();
    // Put the botguy into the tram!
    slowServo(ARM,ARM_PUT,500);
	// slowServo(CLAW,400,1000);
    
    printf("put botguy in tram");
}

void init() {
	printf("Conecting to Create\n");
	// TODO Add light activate
	create_connect();
    	printf("start\n");
    	create_full();
	printf("connected\n");
    
  	enable_servo(ARM);
	enable_servo(CLAW);
	// light here
	slowServo(ARM,ARM_UP,1000);
    
    //set_servo_position(CLAW, CLAW_CLOSE);    //set starting values


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
    
    init();

    //wait_for_light(0);
    //shut_down_in(119);

	//FUNCTIONS
    
    //set_servo_position(ARM,ARM_DOWN);
    //set_servo_position(CLAW,CLAW_CLOSE);
    
    initialDrive();
	GetBotguy();
    
    
	printf("dinit\n");
	dinit();
	return 0;


  
}


