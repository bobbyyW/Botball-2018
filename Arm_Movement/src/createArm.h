


#include <kipr/botball.h>


#define MOTOR_ARM 0
#define WRIST 0
#define CLAW 3

#define BOTGUY_CLOSE 1577
#define DISC_CLOSE 1481
#define FULL_CLOSE 1617
#define CLAW_OPEN 403


void setup() {
  clear_motor_position_counter(MOTOR_ARM);  //position at base, anchored at 0

  clawOpen();

}


void botguyClose() {
  set_servo_position(CLAW, BOTGUY_CLOSE);
}

void clawOpen() {
  set_servo_position(CLAW, CLAW_OPEN);
}


void armUp(int distance, int power) {
  distance = distance * 100;
  
  int initialPosition = get_motor_position_counter(MOTOR_ARM);
  printf("Initial Position: %d", initialPosition);
  power = -1 * power;
  
  motor(MOTOR_ARM, power);
  int difference = abs(gmpc(MOTOR_ARM) - initialPosition);
  while(difference < distance) {
    printf("Position: %d\n", gmpc(MOTOR_ARM));
    msleep(100);
    difference = abs(gmpc(MOTOR_ARM) - initialPosition);
  }
  motor(MOTOR_ARM, 0);
  
}
