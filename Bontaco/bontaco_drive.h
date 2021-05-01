#include "iodefine.h"
#include "bontaco_common.h"
#include "bontaco_encoder.h"
#include "bontaco_battery_watch.h"

void run_straight();
void brake();
void set_target_speed(float);
void pid_control_motor_left();
void pid_control_motor_right();