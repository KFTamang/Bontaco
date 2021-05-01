#include "bontaco_encoder.h"

#define COUNTER_L (MTU1.TCNT)
#define COUNTER_R (MTU2.TCNT)
#define RESET_VALUE (10000)

static int count_diff_left = 0;
static int count_diff_right = 0;
static long count_accu_left = 0;
static long count_accu_right = 0;

unsigned int get_encoder_count(Motor motor){
	
	if(motor == LEFT){
		return COUNTER_L - RESET_VALUE;
	}else if(motor == RIGHT){
		return COUNTER_R - RESET_VALUE;
	}
	return 0;
}

long get_encoder_accumulated_count(Motor motor){
	
	if(motor == LEFT){
		return count_accu_left;
	}else if(motor == RIGHT){
		return count_accu_right;
	}
	return 0;
}

void reset_encoder_accumulated_count(){
	count_accu_left = 0;
	count_accu_right = 0;
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

void update_encoder_diff(Motor motor){
	switch(motor){
		case RIGHT:
			count_diff_right = RESET_VALUE - (int)COUNTER_R;
			count_accu_right += count_diff_right;
			COUNTER_R = RESET_VALUE;
			break;
		case LEFT:
			count_diff_left = (int)COUNTER_L - RESET_VALUE;
			count_accu_left += count_diff_left;
			COUNTER_L = RESET_VALUE;
			break;
		default:
			break;
	}
}

int get_encoder_diff(Motor motor){
	switch(motor){
		case RIGHT:
			return count_diff_right;
			break;
		case LEFT:
			COUNTER_L = RESET_VALUE;
			return count_diff_left;
			break;
		default:
			break;
	}
}