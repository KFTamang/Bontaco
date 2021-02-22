#ifndef BONTACO_MOTOR_PWM_H
#define BONTACO_MOTOR_PWM_H

#include "iodefine.h"
#include "bontaco_common.h"

void disable_motors();
void eable_motors();
void set_duty_ratio(Motor, float);
void set_motor_direction_left(RotationDirection);
void set_motor_direction_left(RotationDirection);

#endif