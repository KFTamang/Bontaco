#include "bontaco_drive.h"
#include "bontaco_led.h"

#define VELOCITY_LOW (200) // [mm/sec], speed of exploration
#define VELOCITY_MIDDLE (1000) // [mm/sec], speed of exploration
#define mV_PER_VELOCITY (0.67)
#define mm_PER_COUNT (25.0*3.1415/30.0*8.0/1024) // distance per encoder count in mm
#define PERIOD (0.001) // time period of drive control, 1ms
#define Kp (0.0001 ) // coefficient for P control

static float target_speed_left = 0;
static float target_speed_right = 0;

void run_stright_with_length(int length_mm){
    long current_count = 0;
    reset_encoder_accumulated_count();
    current_count = (get_encoder_accumulated_count(RIGHT) + get_encoder_accumulated_count(LEFT))/2;
    run_straight();
    ring_buzzer_for_ms(20);
    // loop until the mouse runs for desired length
    while(current_count * mm_PER_COUNT < length_mm){
        current_count = (get_encoder_accumulated_count(RIGHT) + get_encoder_accumulated_count(LEFT))/2;
        wait_ms(100);
    }
    ring_buzzer_for_ms(20);
    brake();
}

void brake(){
    set_target_speed(0);
    enable_motors();
}

void run_straight(){
    set_target_speed(VELOCITY_MIDDLE);
    enable_motors();
}

void set_target_speed(float target_speed){
    target_speed_left = target_speed;
    target_speed_right = target_speed;
}

void pid_control_motor_left(){
    static float current_duty_ratio_left = 0.0;
    float speed_current = get_encoder_diff(LEFT) * mm_PER_COUNT / PERIOD;
    float speed_residue = target_speed_left - speed_current;
    float pid_duty_ratio = speed_residue * Kp; 

    float target_duty_ratio = mV_PER_VELOCITY * VELOCITY_MIDDLE / measure_battery_voltage();
    current_duty_ratio_left = target_duty_ratio + pid_duty_ratio;
    set_duty_ratio(LEFT, current_duty_ratio_left);
}

void pid_control_motor_right(){
    static float current_duty_ratio_right = 0.0;
    float speed_current = get_encoder_diff(RIGHT) * mm_PER_COUNT / PERIOD;
    float speed_residue = target_speed_right - speed_current;
    float pid_duty_ratio = speed_residue * Kp;

    float target_duty_ratio = mV_PER_VELOCITY * VELOCITY_MIDDLE / measure_battery_voltage();
    current_duty_ratio_right = target_duty_ratio + pid_duty_ratio;
    set_duty_ratio(RIGHT, current_duty_ratio_right);
}