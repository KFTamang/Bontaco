#include "bontaco_timer.h"

static unsigned int timer_ms = 0;
static unsigned int timer_sec = 0;

void increment_timer_sec(){
	if(timer_sec == 1000-1){
		timer_sec = 0;
	}else{
		timer_sec++;
	}
}

void increment_timer_ms(){
	if(timer_ms == 1000-1){
		timer_ms = 0;
		increment_timer_sec();
	}else{
		timer_ms++;
	}
}

unsigned int get_timer_ms(){
	return timer_ms;
}

unsigned int get_timer_sec(){
	return timer_sec;
}