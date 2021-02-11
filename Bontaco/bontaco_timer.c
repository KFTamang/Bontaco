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

void wait_ms(unsigned int wait_time_ms){
	unsigned int start_time = get_timer_ms();
	// to avoid overflow, wait time is limited under 10000 ms
	if(wait_time_ms>10000){
		return;
	}
	while(1){
		if((get_timer_ms() - start_time + 10000)%10000 >= wait_time_ms){
			return;
		}
	}
	return;
}

void wait_sec(unsigned int wait_time_sec){
	unsigned int start_time = get_timer_sec();
	// to avoid overflow, wait time is limited under 10000 ms
	if(wait_time_sec>10000){
		return;
	}
	while(1){
		if((get_timer_sec() - start_time + 10000)%10000 >= wait_time_sec){
			return;
		}
	}
	return;
}