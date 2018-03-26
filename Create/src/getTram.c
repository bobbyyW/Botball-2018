#include <kipr/botball.h>
#define black 1100


void create(){
    create_connect();
    create_full();
    int x;
   	while(get_create_rcliff_amt() > black + 200) {
        x = get_create_lfcliff_amt()-(1100+2525)/2;
        create_drive_direct(100+x/10, 100-x/10);
        msleep(1);
    }
    create_drive_straight(100);
    msleep(100);
    create_spin_CW(100);
    msleep(300);
    while(get_create_lfcliff_amt() > black + 200) {
        create_spin_CW(100);
        msleep(1);
    }
    int i = 0;
    while(i < 200) {
        x = get_create_lfcliff_amt()-(1100+2525)/2;
        create_drive_direct(100+x/10, 100-x/10);
        msleep(1);
        i++;
    }
    while(get_create_rcliff_amt() > black + 200) {
        create_drive_straight(-100);
        msleep(1);
    }
    create_drive_straight(100);
    msleep(500);
    create_disconnect();
    
}

