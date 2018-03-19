

#include <kipr/botball.h>

#include "createArm.h"

int main() {
  enable_servos();

  printf("Arjun loves bananas");
  
  setup();
  armUp(30, 50);
  clawOpen();


  return 0;
}
