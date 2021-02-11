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

// wait up to 1000 ms
// if wait_time_ms is larger than 1000 ms, it waits 1000ms
void wait_ms(unsigned int wait_time_ms){
	unsigned int passed_time_ms, start_time_ms = get_timer_ms();
	unsigned int start_time_sec = get_timer_sec();
	// to avoid overflow, wait time is limited to 1000 ms
	if(wait_time_ms>= 1000){
		while(1){
			if( start_time_ms == get_timer_ms() && start_time_sec != get_timer_sec() ){
				break;
			}
		}
	}else{
		while(1){
			passed_time_ms = (get_timer_ms() + 1000 - start_time_ms)%1000 ;
			if(passed_time_ms >= wait_time_ms){
				break;
			}
		}
	}
	return;
}

void wait_sec(unsigned int wait_time_sec){
	unsigned int start_time_sec = get_timer_sec();
	unsigned int start_time_ms = get_timer_ms();

	while(1){
		if((get_timer_sec() - start_time_sec  >= wait_time_sec) && (start_time_ms == get_timer_ms())){
			return;
		}
	}
	return;
}