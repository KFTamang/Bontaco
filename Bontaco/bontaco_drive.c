#include "bontaco_drive.h"

#define SPEED_LOW (25) // [mm/sec], speed of exploration
#define COEF_LEFT (0.005)
#define COEF_RIGHT (0.005)

static unsigned int target_speed_left;
static unsigned int target_speed_right;

void run_straight(){
    set_target_speed(SPEED_LOW);
    enable_motors();
}

void set_target_speed(unsigned int target_speed){
    target_speed_left = target_speed;
    target_speed_right = target_speed;
}

void pid_control_motor_left(){
    set_duty_ratio(LEFT, (float)target_speed_left*COEF_LEFT);
}

void pid_control_motor_right(){
    set_duty_ratio(RIGHT, (float)target_speed_right*COEF_RIGHT);
}