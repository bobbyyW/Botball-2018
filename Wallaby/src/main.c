#include <kipr/botball.h>
void move(x,y,z) {
    motor(1,x);
    motor(2,y);
    msleep(z);
}


int main()
{
  	int min = 800;
    int max = 3300;
    int mean = (min + max)/2;
    int error = (max - min) * 0.05;
    while (1) {
        int x = analog(5);
        printf("%d\n",x);
        if (x > mean + error) { //if it's more on the black turn right
        	move(-75,100,1);
        }
        else if (x < mean - error) { //if it's more on the white turn left
        	move(-100,75,1);
        }
        else {
        	move(-100,100,1); //if it's in the middle turn 0 degrees. YOU'RE A NOOOOOOOOOOOOOOB!!!
        }
    }
    return 0;
}
