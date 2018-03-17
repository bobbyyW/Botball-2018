/////////////////////////////////////////////////////
///// main.c                                    /////
///// botball team 18-0510                      /////
/////////////////////////////////////////////////////

#include <kipr/botball.h>
#include "exmove.h"

// create init (starting)

void init() {
  printf("Connect");
  create_connect();
  
  printf("Begin");
  create_full();
  
  /set all of positions STARTING VALUES
  
  /enable servos
 
}

void dinit() {
  disable_servos();
  create_disconnect():
  printf("Finished");
  
}
