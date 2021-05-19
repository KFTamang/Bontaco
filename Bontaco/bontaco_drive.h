#include "iodefine.h"
#include "bontaco_common.h"
#include "bontaco_encoder.h"
#include "bontaco_battery_watch.h"

void run_straight();
void turn_90_degree(unsigned int, Direction);
void run_straight_with_length(int length_mm);
void brake();
void set_target_velocity(float);
void set_target_angular_velocity(float);
void pid_control_motor_left();
void pid_control_motor_right();