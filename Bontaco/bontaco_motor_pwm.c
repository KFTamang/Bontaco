#include "bontaco_motor_pwm.h"

#define MOTOR_STANDBY (PORTB.PODR.BIT.B7)
#define MOTOR_IN1_R (PORTB.PODR.BIT.B1)
#define MOTOR_IN2_R (PORTB.PODR.BIT.B0)
#define MOTOR_IN1_L (PORTB.PODR.BIT.B5)
#define MOTOR_IN2_L (PORTB.PODR.BIT.B6)

void motor_ready(){
	MOTOR_IN1_R = 0;
	MOTOR_IN2_R = 1;
	MOTOR_IN1_L = 0;
	MOTOR_IN2_L = 1;
	MOTOR_STANDBY = 1;
}

void motor_standby(){
	MOTOR_STANDBY = 0;
}