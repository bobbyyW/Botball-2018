



#ifndef MINIFIED
#include "kipr/botball.h"
#include "initialDrive.h"
#include "createDrive.h"
#include "exmove.h"
#endif

#define black 1500
#define white 2500

void initialDrive() {    
    create_drive_direct(-100,-200);
    msleep(2000); // square up
    printf("rf: %d\n", get_create_rfcliff_amt());
    printf("squared up\n");
    
    while (get_create_rfcliff_amt() > black){
        create_drive_straight(75);
        msleep(1);
    }

    printf("rf: %d\n", get_create_rfcliff_amt());
    printf("rf enter black \n");
    
    // value <= black < white
    while (get_create_rfcliff_amt() < white){
     	create_drive_straight(20);
        msleep(1);  
    }
    printf("rf: %d\n", get_create_lfcliff_amt());
    printf("rf left black \n");
   
    // Rotate right slightly
    create_spin_CW(50);
    msleep(500);
    
    // value >= white > black
    while (get_create_lfcliff_amt() > black){
     	create_drive_straight(75);
        msleep(1);
    }
    printf("lf: %d\n", get_create_lfcliff_amt());    
    printf("lf enter center black line\n");
    
    // Rotate left slightly
    create_spin_CCW(50);
    msleep(500);
    
    // start line follow
    // r >= white > black
 
    int mean = (black + white) / 2;
    int error = (white - black) / 10;
    int lf = get_create_lfcliff_amt();
    printf("r: %d\n", get_create_rcliff_amt());
    printf("lf: %d\n", lf);
    printf("start line follow\n");
    while(get_create_rcliff_amt() > black) {
        lf = get_create_lfcliff_amt();
        if (lf < mean - error){
            // on black turn left
            create_spin_CCW(50);
            msleep((mean - lf)/20);
            // create_drive_direct(75,50);
        } else if (lf > mean + error){
            // on white turn right
            create_spin_CW(50);
            msleep((lf - mean)/20);
            // create_drive_direct(50,75);
        }
        create_drive_straight(75);
        msleep(1);                
    }
    
    printf("right enter black");
    create_stop();
}