#include "bontaco_encoder.h"

#define COUNTER_L (MTU1.TCNT)
#define COUNTER_R (MTU2.TCNT)

unsigned int get_encoder_count(Motor motor){
	
	if(motor == LEFT){
		return COUNTER_L;
	}else if(motor == RIGHT){
		return COUNTER_R;
	}
	return 0;
}