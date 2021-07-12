#include "bontaco_motor_pwm.h"

#define MOTOR_STANDBY (PORTB.PODR.BIT.B7)
#define MOTOR_IN1_R (PORTB.PODR.BIT.B1)
#define MOTOR_IN2_R (PORTB.PODR.BIT.B0)
#define MOTOR_IN1_L (PORTB.PODR.BIT.B5)
#define MOTOR_IN2_L (PORTB.PODR.BIT.B6)
#define MOTOR_PWM_R (MTU4.TGRA)
#define MOTOR_PWM_L (MTU4.TGRC)
#define PWM_MAX (320)

void set_motor_direction_left(RotationDirection dir)
{
	if (dir == FORWARD)
	{
		MOTOR_IN1_L = 1;
		MOTOR_IN2_L = 0;
	}
	else
	{
		MOTOR_IN1_L = 0;
		MOTOR_IN2_L = 1;
	}
}

void set_motor_direction_right(RotationDirection dir)
{
	if (dir == FORWARD)
	{
		MOTOR_IN1_R = 0;
		MOTOR_IN2_R = 1;
	}
	else
	{
		MOTOR_IN1_R = 1;
		MOTOR_IN2_R = 0;
	}
}

void disable_motors()
{
	// when MOTOR_PWM_R/L is PWM_MAX, motor rotation is lowest
	MOTOR_PWM_R = PWM_MAX + 1;
	MOTOR_PWM_L = PWM_MAX + 1;

	MOTOR_IN1_R = 0;
	MOTOR_IN2_R = 0;
	MOTOR_IN1_L = 0;
	MOTOR_IN2_L = 0;

	MOTOR_STANDBY = 0;
}

void enable_motors()
{
	set_motor_direction_left(FORWARD);
	set_motor_direction_right(FORWARD);
	MOTOR_STANDBY = 1;
}

void set_duty_ratio(Motor motor, float duty_ratio)
{
	if (duty_ratio > 1.0)
	{
		duty_ratio = 1.0;
		// if(motor == LEFT){
		// 	set_motor_direction_left(FORWARD);
		// }else if(motor == RIGHT){
		// 	set_motor_direction_right(FORWARD);
		// }
	}
	else if (duty_ratio < 0)
	{
		// duty_ratio = -duty_ratio;
		// if(motor == LEFT){
		// 	set_motor_direction_left(BACKWARD);
		// }else if(motor == RIGHT){
		// 	set_motor_direction_right(BACKWARD);
		// }
		duty_ratio = 0;
	}
	switch (motor)
	{
	case RIGHT:
		MOTOR_PWM_R = (unsigned int)(PWM_MAX + 1 - duty_ratio * PWM_MAX);
		break;
	case LEFT:
		MOTOR_PWM_L = (unsigned int)(PWM_MAX + 1 - duty_ratio * PWM_MAX);
		break;
	default:
		break;
	}
}
