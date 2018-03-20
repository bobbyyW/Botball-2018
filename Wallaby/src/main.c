#include <kipr/botball.h>
void servo(x,y) { //efficient servo positioning
    set_servo_position(x,y);
}

void move(x,y,z) { // efficient moving
	motor(0,x); // 0 is right, 1 left
    motor(1,-y);
	msleep(z);
}

void line_follow(x,y) {
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
    }
}

//void turn_right() { //turn 90 degrees right
	//move(-50,100,680);
//}
//void turn_left() { //turn 90 degrees left
//	move(100,-50,680);
//}

int main()
{   
    int max = 3700;
    int min = 200;
    int mean = (min + max)/2;
    int error = (max - min) * 0.05;
    
    while(analog(5) < mean) {
    	move(50,50,1);
    }
	
    
    while (analog(5) >= mean) {
    	move(25,25,1);
    }
	
    
    while (analog(5) < mean) {
    	printf("%d\n",analog(5));
        move(30,30,1);
    }
    
    
    //turn_right();
    
    while(analog(5) >= mean) {
    	move(-25,25,1);
    }
    
    int open = camera_open();
    printf("%d\n",open);
    int update = camera_update();
    printf("%d\n",update);
    int object_count = get_object_count(0);
    printf("%d\n",object_count);
    
    
    while (1) { // remember to change condition
    	int x = analog(5);
        printf("%d\n",x);
        if (x > mean + error) { // if it's more on the black
        	move(40,80,1);
        }
        else if (x < mean - error) { // if it's more on the white
        	move(80,40,1);
        }
        else {
        	move(80,80,1); // noob
        }
    }
    
    // move(100,0,750);
    // line_follow(60,80);
    
        
    return 0;
}
