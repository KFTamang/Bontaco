#ifndef BONTACO_LED_H
#define BONTACO_LED_H

#include "../iodefine.h"

#define DEBUG_LED_0 (PORTE.PODR.BIT.B3)
#define DEBUG_LED_1 (PORTE.PODR.BIT.B4)
#define DEBUG_LED_2 (PORTE.PODR.BIT.B5)

#define MODE_LED_0 (PORT5.PODR.BIT.B4)
#define MODE_LED_1 (PORT5.PODR.BIT.B5)

#define LED_7SEG_1 (PORT1.PODR.BIT.B4)
#define LED_7SEG_2 (PORT1.PODR.BIT.B5)
#define LED_7SEG_3 (PORT1.PODR.BIT.B6)
#define LED_7SEG_4 (PORT1.PODR.BIT.B7)
#define LED_7SEG_5 (PORT2.PODR.BIT.B7)
#define LED_7SEG_6 (PORT3.PODR.BIT.B1)
#define LED_7SEG_7 (PORT3.PODR.BIT.B2)

void turn_on_debug_led(int);
void turn_off_debug_led(int);
void turn_on_mode_led(int);
void turn_off_mode_led(int);
void display_7seg(int);

#endif // BONTACO_LED_H


