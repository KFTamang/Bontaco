#include "bontaco_buzzer.h"

#define BUZZER (PORTB.PODR.BIT.B3)

static int buzzer_on = 0;
static unsigned int buzzer_timer = 0;

// interrupt function for toggling buzzer's IO
// called at 2*4.0kHz
void toggle_buzzer(){
	if(buzzer_timer > 0){
		BUZZER = ~BUZZER;
	}else{
		BUZZER = 0;
	}
}

void turn_on_buzzer(){
	buzzer_on = 1;
}

void turn_off_buzzer(){
	buzzer_on = 0;
}

// this function is called every 1ms by timer interrupt
void decrement_buzzer_timer(){
	if(buzzer_timer>0){
		buzzer_timer--;
	}
}

void ring_buzzer_for_ms(unsigned int time_ms){
	buzzer_timer = time_ms;
}
