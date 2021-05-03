#include "bontaco_drive.h"
#include "bontaco_led.h"

#define Pi (3.1415)
#define VELOCITY_LOW (200) // [mm/sec], speed of exploration
#define VELOCITY_MIDDLE (1000) // [mm/sec], speed of exploration
#define mV_PER_VELOCITY (60.0*0.470/(8.0/30.0)/Pi/25.0) //1.34649 [mV / (mm/sec)]
#define mV_PER_ANGULAR_V (mV_PER_VELOCITY*75.0*Pi/180.0) // 1.7625 [mV / (deg/sec)]
#define mm_PER_COUNT_RIGHT (25.0*Pi/30.0*8.0/1024) // distance per encoder count in mm
#define mm_PER_COUNT_LEFT (25.0*Pi/30.0*8.0/1024*3.0/2.0) // distance per encoder count in mm
#define deg_PER_COUNT_RIGHT (mm_PER_COUNT_RIGHT*180.0/Pi/75.0) // degree per encoder count difference (i.e. LEFT - RIGHT)
#define deg_PER_COUNT_LEFT (mm_PER_COUNT_LEFT*180.0/Pi/75.0) // degree per encoder count difference (i.e. LEFT - RIGHT)
#define PERIOD (0.001) // time period of drive control, 1ms
#define Kp_V (0.001 ) // velocity coefficient for P control
#define Kp_AV (0.002 ) // angular velocity coefficient for P control

static float target_velocity = 0;
static float target_angular_velocity = 0;
static float dutyratio_v = 0;
static float dutyratio_av = 0;

static float get_velocity(void)
{
    int count_right = get_encoder_diff(RIGHT);
    int count_left  = get_encoder_diff(LEFT);
    float velocity = (mm_PER_COUNT_RIGHT * count_right + mm_PER_COUNT_LEFT * count_left) / 2 / PERIOD;
    return velocity;
}

// angular velocity, + for clockwise, - for counter-clockwise
static float get_angular_velocity(void)
{
    int count_right = get_encoder_diff(RIGHT);
    int count_left  = get_encoder_diff(LEFT);
    float angular_velocity = (deg_PER_COUNT_LEFT * count_left - deg_PER_COUNT_RIGHT * count_right) / PERIOD;
    return angular_velocity;
}

float get_path_length(void)
{
    long count_right = get_encoder_accumulated_count(RIGHT);
    long count_left = get_encoder_accumulated_count(LEFT);
    float path_length = 0;
    path_length = count_right * mm_PER_COUNT_RIGHT + count_left * mm_PER_COUNT_LEFT;
    path_length /= 2.0;
    return path_length;
}

static void reset_path_length(void)
{
    reset_encoder_accumulated_count();
}

void run_straight_with_length(int length_mm)
{
    reset_path_length();
    run_straight();
    ring_buzzer_for_ms(10);
    // loop until the mouse runs for desired length
    while( get_path_length() < length_mm ){
        wait_ms(100);
    }
    ring_buzzer_for_ms(10);
    brake();
}

void brake(void)
{
    set_target_velocity(0);
    enable_motors();
}

void run_straight(void)
{
    set_target_velocity(VELOCITY_LOW);
    enable_motors();
}

void set_target_velocity(float _target_velocity)
{
    target_velocity = _target_velocity;
}

void set_motor_duty_ratios(void)
{
    float dutyratio_left = dutyratio_v + dutyratio_av/2;
    float dutyratio_right = dutyratio_v - dutyratio_av/2;
    set_duty_ratio(RIGHT, dutyratio_right);
    set_duty_ratio(LEFT, dutyratio_left);
}

void pid_control_velocity(void)
{
    float target_duty_ratio = mV_PER_VELOCITY * target_velocity / measure_battery_voltage();
    float current_velocity = get_velocity();
    float residue_velocity = target_velocity - current_velocity;
    float pid_duty_ratio = residue_velocity * Kp_V; 

    dutyratio_v = target_duty_ratio + pid_duty_ratio;
}

void pid_control_angular_velocity(void)
{
    float target_duty_ratio = mV_PER_ANGULAR_V * target_angular_velocity / measure_battery_voltage();
    float current_av = get_angular_velocity();
    float residue_av = target_angular_velocity - current_av;
    float pid_duty_ratio = residue_av * Kp_AV; 

    dutyratio_av = target_duty_ratio + pid_duty_ratio;
}