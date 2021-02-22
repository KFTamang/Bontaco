#include "bontaco_encoder.h"

#define COUNTER_L (MTU1.TCNT)
#define COUNTER_R (MTU2.TCNT)
#define RESET_VALUE (10000)

unsigned int get_encoder_count(Motor motor){
	
	if(motor == LEFT){
		return COUNTER_L - RESET_VALUE;
	}else if(motor == RIGHT){
		return COUNTER_R - RESET_VALUE;
	}
	return 0;
}

void reset_encoder_count(Motor motor){
	switch(motor){
		case RIGHT:
			COUNTER_R = RESET_VALUE;
			break;
		case LEFT:
			COUNTER_L = RESET_VALUE;
			break;
		default:
			break;
	}
}