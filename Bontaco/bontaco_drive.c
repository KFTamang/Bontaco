#include "bontaco_drive.h"

#define SPEED_LOW (200) // [mm/sec], speed of exploration
#define SPEED_PER_DUTYRATIO_LEFT (0.0005)
#define SPEED_PER_DUTYRATIO_RIGHT (0.0005)
#define mm_PER_COUNT (25.0*3.1415/30.0*8.0/1024) // distance per encoder count in mm
#define PERIOD (0.001) // time period of drive control, 1ms

static float target_speed_left = 0;
static float target_speed_right = 0;

void run_straight(){
    set_target_speed(SPEED_LOW);
    enable_motors();
}

void set_target_speed(float target_speed){
    target_speed_left = target_speed;
    target_speed_right = target_speed;
}

void pid_control_motor_left(){
    static float current_duty_ratio_left = 0.0;
    float speed_current = get_encoder_diff(LEFT) * mm_PER_COUNT / PERIOD;
    float speed_residue = speed_current - target_speed_left;
    current_duty_ratio_left -= speed_residue*SPEED_PER_DUTYRATIO_LEFT; 

    set_duty_ratio(LEFT, current_duty_ratio_left);
}

void pid_control_motor_right(){
    static float current_duty_ratio_right = 0.0;
    float speed_current = get_encoder_diff(RIGHT) * mm_PER_COUNT / PERIOD;
    float speed_residue = speed_current - target_speed_right;
    current_duty_ratio_right -= speed_residue*SPEED_PER_DUTYRATIO_RIGHT;

    set_duty_ratio(RIGHT, current_duty_ratio_right);
}