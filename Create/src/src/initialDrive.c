#ifndef MINIFIED
#include "kipr/botball.h"
#include "initialDrive.h"
#include "createDrive.h"
#include "createDrive.c"
#endif

void initialDrive() {    
    
    
    int black = 1100;
    int white;
    
    //start the initialdrive
    
    create_drive_direct(-100,-250);
    msleep(1500); // square up
    white = get_create_rcliff_amt();
    printf("rf: %d\n", get_create_rfcliff_amt());
    printf("squared up\n white : %d\n", white);
    
/*
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

 */
    
   int i;
   for (i = 0; i < 1800; i++){
       
       /*
           int value = get_create_lfcliff_amt();
       	   if (value < black){
               black = value;
           }
           */

   		   create_drive_straight(40);
   		   msleep(1);
   }
	int mean = (black + white)/2;
    int error = (white - black) * 0.2;
    printf("black: %d white : %d mean : %d error : %d \n", black, white, mean, error);
    printf("rf left black \n");
  

    // Rotate right slightly
    create_spin_CW(140);
    msleep(750);
    
    // value >= white > black
    while (get_create_lfcliff_amt() > white - error){
     	create_drive_straight(100);
        msleep(1);
    }
    
    printf("slightly past center line");
    printf("lf: %d\n", get_create_lfcliff_amt());    
    printf("lf enter center black line\n");

    /*
    while (get_create_lfcliff_amt() < white - error){
     	create_drive_straight(40);
        msleep(1);  
    }
    
    */
    
    create_drive_straight(100);
    msleep(500);
    
        
    create_drive_straight(100);
    msleep(250);
    
    // Rotate left slightly
    create_spin_CCW(140);
    msleep(750);

    
    
    
    // start line follow
    // r >= white > black
 
    int lf = get_create_lfcliff_amt();
    printf("r: %d\n", get_create_rcliff_amt());
    printf("lf: %d\n", lf);
    printf("start line follow\n");
    
    while(get_create_rcliff_amt() > black + error*2) {
        int x = get_create_lfcliff_amt() - mean;
        create_drive_direct(100+x/20, 100-x/20);
        msleep(1);
    }
    
    /*
    
    if (l < black + error){
	// crossed the center line
	create_spin_CCW(100);
	msleep(1);
   	printf(" l : %d \n", l);
    }
    while(get_create_rcliff_amt() > black + error) {
        lf = get_create_lfcliff_amt();
        if( lf > white - error) {
            create_spin_CCW(75);
            continue;
    	}else if (lf < black + error){
            create_spin_CW(75);
            continue;
        }else{
            create_drive_straight(90);
        }
        msleep(1);
    }
    */
    
    
    
    printf("got to goal");
    
    // Henry's code
    printf("spin\n");
    /*
    int q;
    for (q = 0; q < 3; q ++){
    while(get_create_lfcliff_amt() > black + error) {
        create_spin_CW(50);
        msleep(1);
    }
    */
    //UNTESTED
    create_spin_CW(100);
    msleep(500);
    int p;
    for (p = 0; p<2;p++){
        
    create_spin_CW(50);
    msleep(500);
    
    while(get_create_rfcliff_amt() > black + error) {
        create_spin_CW(50);
        msleep(1);
    	}
    }
    create_spin_CCW(100);
    msleep(1000);


    //GET TO THE POSITION TO GRAB THE BOTGUY
    //FOR NO
    
    //move down the MOTOR to starting pos
    //get both the claw and arm into pos
    //move forward to grab it
    //close claw
    //move back
    //move up the arm MOTOR
    
    
    //TURN 180 DEGREES 
    
    //Put Botguy in the Tram
    
    /*
    
    printf("forward until lf \n");
    
    int z = 0;
    while(z < 200) {
        int x = get_create_lfcliff_amt()- mean;
        create_drive_direct(100+x/20, 100-x/20);
        msleep(1);
        z++;
    }
    
    
    
    
    //START TO GET THE TRAM
    
    while(get_create_rcliff_amt() > black + error * 2) {
        create_drive_straight(-100);
        msleep(1);
    }
    
    create_drive_straight(-100); // maybe use distance?? correct create pos for setup
    msleep(1000);
    
    printf("get into the correct pos for setup");
    
    
    motor(0,-90); // move the arm into the correct position
    msleep(4000);
    
    printf("got the motor arm into pos.");
   
    
    //move the arm
    
    //move the claw to open
    
    printf("move arm + open claw");
    
    //get into position to grab
    
    printf("move forward to grab");
    
    //close claw
    
    printf("grab");
    
    create_drive_straight(100);
    //until in pos : probably go till hits that wall thing
    msleep(3000);
    
    printf("move forward until no longer can... proceed to push to the end");
    
    
    //
    
    */
    
    create_stop();

    
}