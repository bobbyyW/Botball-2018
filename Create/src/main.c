///////////////////////////////////////////////////////////////
// main.c                             //
// For use by botball team 18-0510                           //
///////////////////////////////////////////////////////////////

#include <kipr/botball.h>
#define ARM 2
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

int black = 1100;
int white = 2750;
int mean;
int error;

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

void move_arm(int motor, int speed, int pos) {
    int old_pos = get_motor_position_counter(motor);
    int new_pos = old_pos;
    do {
	    move_to_position(motor,speed,pos);
    	block_motor_done(motor);
    	new_pos = get_motor_position_counter(motor);
        printf("move_arm: old %d, cur %d, target %d\n", old_pos, new_pos, pos);
    } while (abs(pos - new_pos) > abs(new_pos - old_pos));
}

void square_up(int dir) {
    int speed = 50 * dir;
    int half_speed = 25 * dir;
    
    printf("Square up initial: right %d, left %d\n", get_create_rcliff_amt(), get_create_lcliff_amt());
    while(get_create_lcliff_amt() > mean && get_create_rcliff_amt() > mean) {
        create_drive_direct(speed, speed);
        msleep(1);
    }
    printf("Square up after loop 1: right %d, left %d\n", get_create_rcliff_amt(), get_create_lcliff_amt());
    
    // Square up on black line
    while(get_create_lcliff_amt() > mean) {
      	create_drive_direct(half_speed, 0);
        msleep(1);
    }
    printf("Square up after loop 2: right %d, left %d\n", get_create_rcliff_amt(), get_create_lcliff_amt());
    
    while(get_create_rcliff_amt() > mean) {
        create_drive_direct(0, half_speed);
        msleep(1);
    }
    printf("Square up after loop 3: right %d, left %d\n", get_create_rcliff_amt(), get_create_lcliff_amt());
    
    int r = get_create_rcliff_amt();
    int l = get_create_lcliff_amt();
    while (abs(r - l) > error) {
    	if (r > l) { // right more on white
            create_drive_direct(-half_speed, half_speed);
        } else {
            create_drive_direct(half_speed, -half_speed);
        }
    	r = get_create_rcliff_amt();
    	l = get_create_lcliff_amt();
    }
    
    printf("Squared up: right %d, left %d\n", get_create_rcliff_amt(), get_create_lcliff_amt());
}
void setUpServos() {
    enable_servos();
    set_servo_position(1, 300);
    set_servo_position(2, 1800);
    msleep(500);
    move_arm(0,750,1500);
}
void initialDrive() {    

#define clawDisk 400
#define clawOpen 1471
#define arm 2
#define claw 1
        
    // move the arm to horizontal position
    msleep(500);
    move_arm(MOTOR,1000,0);
    
    // Wait for wallaby to pick up the yellow blocks
    msleep(5000);
    
    // square up on the bottom side
    create_drive_direct(-100,-250);
    msleep(2000);
    // white = get_create_lcliff_amt();
    mean = (black + white) / 2;
    error = (white - black) * 0.1;
    printf("mean: %d, error: %d, black: %d, white: %d\n", mean, error, black, white); 
    
    //move forward to align with the frisbee
    create_drive_straight(100);
    msleep(600);
    // rotate 90 degrees
    create_drive_direct(-100,100);
    msleep(1600);
    
    // move towards the frisbee by moving backward since the arm is facing the back
    square_up(-1);
    
    // move past both black lines
    create_drive_direct(-50, -50);
    msleep(3000);

    // move while both left and right sensors are on white
    // square up on the second black line
    square_up(1);
    
    create_stop();
    msleep(300);
    
    // debug
    printf("after exiting initial block\n");
    // msleep(5000);

    // Lower arm for the frisbee
    move_arm(MOTOR,750,800);

    // Open claw
    slowServo(claw, clawOpen+400, 1000);
    // Move wrist to position
    slowServo(arm, 750, 500);
    
    // Move towards frisbee
    create_drive_direct(-100, -100);
    msleep(1300);
    create_stop();
    msleep(1000);
    
    // Close claw to GRAB THE FRISBEE
    slowServo(claw, clawDisk, 1000);
    msleep(300);
    // Raise wrist
    slowServo(arm, 500, 1500);
    msleep(300);

    square_up(1);
    create_stop();
    
    // Move past the black line
    create_drive_direct(100, 100);
    msleep(450);
    // Turn right 90 degree to align with the black line
    create_spin_CW(100);
    msleep(1500);

    // debug
    printf("before line follow\n");
    // create_stop();
    // msleep(5000);
    
    // Follow vertical line using left front sensor until right sensor is on horizontal black line.
    int cou = 0;
    while(cou < 1000) {
    	int x = get_create_lfcliff_amt() - mean;
        create_drive_direct(100+x/23,100-x/23);
        msleep(1);
        cou++;
    }
    while(get_create_rcliff_amt() > mean) {
    	int x = get_create_lfcliff_amt() - mean;
        create_drive_direct(50+x/46,50-x/46);
        msleep(1);
    }
    
    // Move the right cliff sensor past the black line so that the create is positioned correctly (veritcally)
    while( get_create_rcliff_amt() <= mean){
        create_drive_straight(25);
        msleep(1);
    }
    create_drive_straight(50);
    msleep(350);

    create_stop();
    msleep(300);
    
    // debug
    printf("after line follow\n");
    // msleep(5000);

    
    // Raise arm
    move_arm(0,750,MOTOR_UP);
    
    // Turn right so that the left front sensor is not on black.
    create_spin_CW(100);
    msleep(1000);
    
    // Square up until the left front sensor is on horizontal black line.
   	while(get_create_lfcliff_amt() > mean){
        create_spin_CW(100);
    	msleep(1);
    }
    // create_spin_CW(100);
    // msleep(125); //DELETE IF NOT NEEDED
    
    // debug
    printf("before moving to tram\n");
    // create_stop();
    // msleep(5000);
    
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
    msleep(3000);
    printf("spun");
    create_stop();
    
    // Lower the arm before moving towards the botguy
    // Close claw
    slowServo(claw,CLAW_CLOSE,500);
    // Lower arm
    msleep(300);
    move_arm(MOTOR_ARM,MOTOR_MOVE,MOTOR_DOWN_POS);
    // Lower wrist
    slowServo(ARM,580,1500);

    // Move towards botguy while both right and left sensors are on white
    // Square up on vertical black line
    create_drive_straight(50);
    msleep(1000);
    square_up(-1);
        
    // Spin to the left slightly.
    create_spin_CCW(25);
    msleep(600);

    // debug
    printf("before moving to box\n");
    // create_stop();
    // msleep(5000);

    // Move into box 
    create_drive_direct(-100,-100);
    msleep(850);
    create_stop();
    
    // Open claw
    slowServo(CLAW,CLAW_MID,1000);
    // Lower wrist
    slowServo(ARM,680,1000);
    // Move towards botguy
    printf("Last move to botguy: rf %d, lf %d\n", get_create_rfcliff_amt(), get_create_lfcliff_amt());
    create_drive_straight(-100);
    msleep(1500);
    create_stop();
    // Grab botguy
    slowServo(CLAW,BOTGUY_CLOSE,1000);
    create_drive_straight(100);
    msleep(500);
    create_stop();
    // Wait for wallaby to pass by
    msleep(5000);
    // Move back while both left and right sensors are on white
    // Square up on vertical line
    square_up(1);

    // debug
    printf("after grabbing botguy\n");
    // create_stop();
    // msleep(5000);

    // Move back a bit more so that there is room to raise arm
    create_drive_straight(100);
    msleep(1750);
    create_stop();
    printf("got the guy, out of the box");
    msleep(300);
    
    
    // Raise arm
    move_arm(MOTOR,MOTOR_MOVE-150,MOTOR_UP);
    printf("finished getting arm into pos to go backwards then drop");
    // Raise wrist
    slowServo(ARM,ARM_UP,1000);    
    // Turn 180 degree
    create_drive_direct(100,-100);
    msleep(3200);
    
    // Move towards the tram while both left and right sensors are on white
    // Square up on vertical line
    square_up(1);
    
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
    //setUpServos();


    wait_for_light(0);
    shut_down_in(119);
    init();

	//FUNCTIONS
    
    //set_servo_position(ARM,ARM_DOWN);
    //set_servo_position(CLAW,CLAW_CLOSE);
    
    initialDrive();
	GetBotguy();
    
    
	printf("dinit\n");
	dinit();
    //move_arm(0, 1000, 0);
	return 0;


  
}
