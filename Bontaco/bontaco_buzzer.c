#include "bontaco_buzzer.h"

#define BUZZER (PORTB.PODR.BIT.B3)

static int buzzer_on;

// interrupt function for toggling buzzer's IO
// called at 2*2.7kHz
void toggle_buzzer(){
	if(buzzer_on){
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
