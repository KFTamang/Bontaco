#include "bontaco_motor_pwm.h"

#define MOTOR_STANDBY (PORTB.PODR.BIT.B7)
#define MOTOR_IN1_R (PORTB.PODR.BIT.B1)
#define MOTOR_IN2_R (PORTB.PODR.BIT.B0)
#define MOTOR_IN1_L (PORTB.PODR.BIT.B5)
#define MOTOR_IN2_L (PORTB.PODR.BIT.B6)
#define MOTOR_PWM_R (MTU4.TGRA)
#define MOTOR_PWM_L (MTU4.TGRC)
#define PWM_MAX (320)

extern float duty_right;
extern float duty_left;

void set_motor_direction_left(RotationDirection dir)
{
}

void set_motor_direction_right(RotationDirection dir)
{
}

void disable_motors()
{
}

void enable_motors()
{
}

void set_duty_ratio(Motor motor, float duty_ratio)
{
    if (motor == RIGHT)
    {
        duty_right = duty_ratio;
    }
    else if (motor == LEFT)
    {
        duty_left = duty_ratio;
    }
}
