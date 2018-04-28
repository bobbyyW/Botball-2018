#include <kipr/botball.h>
void move(x,y,z) {
    motor(1,x);
    motor(2,y);
    msleep(z);
}


int main()
{
	camera_open();
    
    int count = 20;
    int sum_area_0 = 0;
    double sum_conf_0 = 0;
    int sum_area_others = 0;
    double sum_conf_others = 0;
    int count_others = 0;
    int x = 0;
    for (x = 0; x<count; x++) {
    	camera_update();
        int object_count = get_object_count(0);
        printf("Object count: %d\n", object_count);
        int i;
        for (i = 0; i < object_count; i++) {
        	int object_area = get_object_area(0,i);
        	double object_confidence = get_object_confidence(0,i);
            if (i == 0) {
                sum_area_0 += object_area;
                sum_conf_0 += object_confidence;
            } else {
                sum_area_others += object_area;
                sum_conf_others += object_confidence;
 				count_others++; 
            }
    	}
    }

    double avg_area_0 = sum_area_0 / (double)count;
    double avg_conf_0 = sum_conf_0 / (double)count;
    double avg_area_others = sum_area_others / (double)count_others;
    double avg_conf_others = sum_conf_others / (double)count_others;
    printf("Average object 0 area: %lf\n", avg_area_0);
    printf("Average object 0 confidence: %lf\n", avg_conf_0);
    printf("Average other object area: %lf\n", avg_area_others);
    printf("Average other object confidence: %lf\n", avg_conf_others);
    printf("Object area threshold: %lf\n", (avg_area_0 + avg_area_others) / 2.0);
    printf("Object confidence threshold: %lf\n", (avg_conf_0 + avg_conf_others) / 2.0);
    
    return 0;
}
