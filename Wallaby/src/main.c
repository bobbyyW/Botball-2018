#include <kipr/botball.h>

int max = 3400;
int min = 170;
int area_thresh = 4607;
float confidence_thresh = 0.48;
int mean;
int error;

void servo(x,y) { //efficient servo positioning
    set_servo_position(x,y);
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

void move(x,y,z) { // efficient moving
	motor(0,x); // 0 is right, 1 left
    motor(1,-y);
	msleep(z);
}

int detect_crate() {
    static int count = 0;
    
	// camera_open();
    camera_update();
    if (get_object_count(0) <= 0) {
        count = 0;
        return 0;
    }
    
    int object_area = get_object_area(0,0);
    double object_confidence = get_object_confidence(0,0);
    if (object_area > area_thresh && object_confidence > confidence_thresh) {
        count++;
        printf("Detected crate: area %d, conf %lf, count %d\n", object_area, object_confidence, count);
        if (count > 3) {
    		return 1;
        } else {
            return 0;
        }
    }
    else {
        count = 0;
    	return 0;
    }
}

void square_up(speed) {
    // square up on black
    int slow = speed / 2;
    int reverse = -slow / 2;
    
    printf("square up initial: right %d, left %d\n", analog(1), analog(5));
    // move forward until either sensor is on black, or move forward while both sensors are on white
    while (analog(1) < mean && analog(5) < mean) {
    	move(speed,speed,1);
    }
    printf("square up loop 1: right %d, left %d\n", analog(1), analog(5));
    while (analog(1) < mean) { // right is on white, move left
        // move left
        move(slow,reverse,1);
    }
    printf("square up loop 2: right %d, left %d\n", analog(1), analog(5));
    while (analog(5) < mean) {
        // move right
        move(reverse,slow,1);
    }
    printf("square up loop 3: right %d, left %d\n", analog(1), analog(5));
    int right = analog(1);
    int left = analog(5);
    while (abs(right - left) > error) {
     	if (right < left) { // right is more on white, move left
            move(slow, -slow, 1);
        } else {
            move(-slow, slow, 1);
        }
        right = analog(1);
        left = analog(5);
    }
    printf("Squared up on black: right %d, left %d\n", analog(1), analog(5));
}

int main()
{   
    mean = (min + max)/2;
    error = (max - min) * 0.05;
    int black = mean - error * 2;
    int white = mean + error * 2;
    
    enable_servos();
    int open = camera_open();
    printf("opened: %d\n",open);
    int update = camera_update();
    printf("updated: %d\n",update);
    int object_count = get_object_count(0);
    printf("object count: %d\n",object_count);
    
    // wait_for_light(0);
    shut_down_in(119);
    
    
    servo(0,1060);
    servo(2,1000);

    // Enter the first black line
    square_up(50);
	
    // Exit the first black line
    
    while (analog(1) >= black || analog(5) >= black) {
    	move(10,10,1);
    }
	
    // Enter the second black line
    square_up(30);
    
    // Exit the second black line
    while (analog(1) >= black || analog(5) >= black) {
    	move(25,25,1);
    }
    //move(10,10,500);
    
    // Turn right 90 degree until right sensor is on black
    while(analog(1) < mean) {
    	move(0,25,1); // regular -25, 25
    }
    
    // Line follow with right sensor while left sensor is on white
    while (analog(5) < white) {
        int x = analog(1);
        if (x > mean + error) { // if it's more on the black, move left
            move(80,60,1);
        }
        else if (x < mean - error) { // if it's more on the white, move right
            move(60,80,1);
       }
        else {
        	move(80,80,1); // noob
        }
    }
    // stop motor before moving the claw
    move(0,0,1);
    
    // debug
    printf("End of line follow: right %d, left %d\n", analog(1), analog(5));
    // msleep(5000);
    
    slowServo(2,340, 1000); // raise the claw before the noobish turn
    
    // Turn left until left sensor is on white
    while(analog(5) > mean - error) {
    	move(25,0,1);
    }
    move(25,0,500); //hardcoded turning 
    move(0,0,1);

    //debug
    printf("Before moving to box \n");
    // msleep(5000);
    
    // Go forward a bit more
    move(25,25,600);//originally 25,0,720
    // stop the motor
    move(0,0,1);
    slowServo(2,1300, 1000);//move it down before the pickup
    
    // Move forward to reach the yellow block
    move(50,50,850);
    
    // stop the motor
    // Close the claws to grab the yellow block
    move(0,0,1);
    slowServo(0,250,1000);
    //msleep(500);
    // Raise the claws
    move(0,0,1);
    slowServo(2,1200,1000);   
    
    //Move backward
    move(-50,-50,7000); // regular 4250
    
    // move forward until the right sensor is on white
    printf("After backing up: %d\n",analog(1));
    while(analog(1) >= black) {
    	move(10,10,1);
    }
    printf("After moving forward: %d\n",analog(1));

    // Turn right until the right sensor in on black
    move(0,25,500);
    while(analog(1) < mean) {
    	move(0,25,1);
    }
    printf("After turning right %d\n",analog(1));
    
    //get in good position for line follow
    move(25,0,1000);
    
    slowServo(2,1184,500);

    // line follow forward 'till left sensor hits black line
    while (analog(5) < white) {
    	int x = analog(1);
        if (x > mean + error) {
        	move(60,40,1);
        }
        else if (x < mean - error) {
        	move(40,60,1);
        }
        else {
        	move(60,60,1);
        }
        
    }
    
    // move a bit so that the left sensor is not on black
    move(25,-25,2000);
    while (analog(5) < mean) {
    	move(25,-25,1);
    }
    move(25,-25,400);
    move(0,0,1);
    //move(-25,25,500);
    
    //raise slightly
    slowServo(2,1150,1000);
    move(0,0,1);
    
    //wait for iCreate
    //msleep(2500);
    
    int lf_distance = 0;
    
    //line follow with left sensor forwards until detecting crate
    while(detect_crate() == 0) {
    	int x = analog(5);
        if (x > mean + error) {
        	move(60,80,1);//was 60,80,1
        }
        else if (x < mean - error) {
        	move(80,60,1);
        }
        else {
        	move(80,80,1);
        }
        lf_distance++;
    }
    printf("LF Distance: %d\n",lf_distance);
    
    int i;
    //line follow with left sensor for a fixed distance
    for (i = 0; i < 550; i++) { //regular 600
    	int x = analog(5);
        if (x > mean + error) {
        	move(30,40,1);
        }
        else if (x < mean - error) {
        	move(40,30,1);
        }
        else {
        	move(40,40,1);
        }
    }
    // stop the motor
    move(0,0,1);
    printf("first block location\n");
    // debug
    // msleep(5000);
    
    // raise the arm
    slowServo(2,950,1000);
    // turn back left
    move(0,-25,3000);
    square_up(25);
    // move back a bit to have room to drop the blocks
    move(-50,-50,650);
    // stop
    move(0,0,1);
    // lower the arm
    slowServo(2,1300,500);
    // open the claw to drop the blocks
    slowServo(0,1000,500);
    // move forward to pick up the top block
    move(40,40,250);
    move(0,0,1);
    // raise the arm for the pickup
    slowServo(2,1000,500);
	// close the claw for the pickup
    slowServo(0,400,400);
	// raise the arm for the extraction
    slowServo(2,700,250);
    printf("dropped the first block\n");
    // debug
    // msleep(5000);
    
    //get out of the way by turning right and line following
    if (lf_distance > 60 && lf_distance < 120) {
    	square_up(25);
    	move(-25,25,2000);
    	for (i=0;i<2000;i++) {
    		int x = analog(5);
        	if (x > mean + error) {
        		move(40,60,1);
        	}
        	else if (x < mean - error) {
        		move(60,40,1);
        	}
        	else {
        		move(60,60,1);
        	}
    	}
        move(0,0,1);
        return 0;
    } // else continue to drop the second block

    // turn left 90 degree to be parallel to the vertical line
    square_up(25);
    move(25,-25,2000);
    printf("parallel position\n");
    // debug
    // move(0,0,1);
    // msleep(5000);
    
    // line follow with right sensor for a fixed distance
    for (i = 0; i < 1450; i++) { //regular 1350
    	int x = analog(1);
        if (x > mean + error) { // if it's on the black, move left
        	move(40,20,1);
        } else if (x < mean - error) { //if it's on the white, move right
        	move(20,40,1);
        }
        else { // move straight
        	move(30,30,1);
        }   
    }
    printf("second block location\n");
    // debug
    // move(0,0,1);
    // msleep(5000);
    
    //make a right turn 90 degree to be perpenticular to the black line
    move(-25,0,3500);
    square_up(25);
    // move back a bit to have room to drop the blocks
    move(-50,-50,650);
    move(0,0,1);
    printf("ready to drop the second block\n");
    // debug
    // msleep(5000);
    
    //place the block
    slowServo(2,1150,500);
    slowServo(0,1000,500);
    slowServo(2,500,500);
        
    return 0;
}

