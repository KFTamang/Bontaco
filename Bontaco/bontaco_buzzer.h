#ifndef BONTACO_BUZZER_H
#define BONTACO_BUZZER_H

#include "iodefine.h"

void toggle_buzzer();
void turn_on_buzzer();
void turn_off_buzzer();
void decrement_buzzer_timer();
void ring_buzzer_for_ms(unsigned int time_ms);

#endif