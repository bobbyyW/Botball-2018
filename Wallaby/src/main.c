#include <kipr/botball.h>
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

/*void line_follow(x,y) {
	int max = 3700;
    int min = 200;
    int mean = (min + max)/2;
    int error = (max - min) * 0.05;
    while (1) {
    	int x = analog(5);
        printf("%d\n",x);
        if (x > mean + error) { // if it's more on the black
        	move(x,y,1);
        }
        else if (x < mean - error) { // if it's more on the white
        	move(y,x,1);
        }
        else {
        	move(y,y,1); // noob
        }
    }*/


//void turn_right() { //turn 90 degrees right
	//move(-50,100,680);
//}
void turn_left(x) { //turn 90 degrees left
	move(100,-50,540 - x);
}

int main()
{   
    enable_servos();
    servo(0,909);
    servo(2,1400);
    int max = 3700;
    int min = 200;
    int mean = (min + max)/2;
    int error = (max - min) * 0.05;
    int open = camera_open();
    printf("opened: %d\n",open);
    int update = camera_update();
    printf("updated: %d\n",update);
    int object_count = get_object_count(0);
    printf("object count: %d\n",object_count);
    int i;
    for (i = 0; i < object_count; i = i + 1) {
        int object_area = get_object_area(0,0);
   		printf("object %d area: %d\n", i, object_area);
    }
    
    //exit(0);
    
    // Enter the first black line
    while(analog(1) < mean) {
    	move(50,50,1);
    }
	
    // Exit the first black line
    while (analog(1) >= mean) {
    	move(25,25,1);
    }
	
    // Enter the second black line
    while (analog(1) < mean) {
    	printf("%d\n",analog(5));
        move(30,30,1);
    }
    
    // Exit the second black line
    while (analog(1) >= mean - error) {
    	move(25,25,1);
    }
   
    //turn_right();
    
    // Turn right until left sensor is on black
    while(analog(1) < mean) {
    	move(0,25,1); // regular -25, 25
    }
    
    while (analog(5) < mean) { // remember to change condition
        int x = analog(1);
        printf("right sensor: %d\n",x);
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
    slowServo(2,340, 1000); // raise the claw before the noobish turn
    
    // Turn left
    while(analog(5) > mean - error) {
    	move(25,0,1);
    }
    
    // Turn left a bit more
    move(25,0,720);
    // stop the motor
    move(0,0,1);
    slowServo(2,1350, 1000);//move it down before the pickup
    
    // Move forward to reach the yellow block
    move(50,50,1000);
    
    // stop the motor
    // Close the claws
    move(0,0,1);
    slowServo(0,250,1000);
    //msleep(500);
    // Raise the claws
    move(0,0,1);
    slowServo(2,1200,1000);
    
    // Move backward
    move(-50,-50,4250);
        
    // line square up
    int left = analog(5);
    int right = analog(1);
    while (!(right < mean + error && right > mean - error && left < mean + error && left > mean - error)) {
    	if (right < mean - error && left > mean + error) { // if right sensor is off but left is one, turn right
        	move(-25,25,1);
        }
        else if (right > mean + error && left > mean + error) {
        	move(25,25,1);
        }
        else if (right < mean - error && left < mean - error) {
        	move (-25,-25,1);
        }
        else if (right > mean + error && left < mean - error) { // if right on black and left on white
        	move(25,-25,1);
        }
        else {
        	printf(" Noobish error. Right %d left %d\n", right, left);
        }
        right = analog(1);
        left = analog(5);
    }
    
    // Move right slightly so the right sensor is on white
    //move(0,25,1000);
    
    /*// Turn right until the right sensor in on black
    while(analog(1) < mean) {
    	move(0,25,1);
    }*/
    
        
    return 0;
}
