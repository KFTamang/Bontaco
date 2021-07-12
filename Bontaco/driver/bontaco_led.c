#include "bontaco_led.h"

#define ON (0)
#define OFF (1)

void turn_on_debug_led(int i)
{

	switch (i)
	{
	case 0:
		DEBUG_LED_0 = ON;
		break;
	case 1:
		DEBUG_LED_1 = ON;
		break;
	case 2:
		DEBUG_LED_2 = ON;
		break;
	default:
		break;
	}
}

void turn_off_debug_led(int i)
{

	switch (i)
	{
	case 0:
		DEBUG_LED_0 = OFF;
		break;
	case 1:
		DEBUG_LED_1 = OFF;
		break;
	case 2:
		DEBUG_LED_2 = OFF;
		break;
	default:
		break;
	}
}

void turn_on_mode_led(int i)
{

	switch (i)
	{
	case 0:
		MODE_LED_0 = ON;
		break;
	case 1:
		MODE_LED_1 = ON;
		break;
	default:
		break;
	}
}

void turn_off_mode_led(int i)
{

	switch (i)
	{
	case 0:
		MODE_LED_0 = OFF;
		break;
	case 1:
		MODE_LED_1 = OFF;
		break;
	default:
		break;
	}
}

void display_7seg(int i)
{
	switch (i)
	{
	case 0:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = OFF;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = ON;
		LED_7SEG_6 = ON;
		LED_7SEG_7 = ON;
		break;
	case 1:
		LED_7SEG_1 = OFF;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = OFF;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = OFF;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = OFF;
		break;
	case 2:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = OFF;
		LED_7SEG_5 = ON;
		LED_7SEG_6 = ON;
		LED_7SEG_7 = OFF;
		break;
	case 3:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = ON;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = OFF;
		break;
	case 4:
		LED_7SEG_1 = OFF;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = OFF;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = ON;
		break;
	case 5:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = OFF;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = ON;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = ON;
		break;
	case 6:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = OFF;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = ON;
		LED_7SEG_6 = ON;
		LED_7SEG_7 = ON;
		break;
	case 7:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = OFF;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = OFF;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = ON;
		break;
	case 8:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = ON;
		LED_7SEG_6 = ON;
		LED_7SEG_7 = ON;
		break;
	case 9:
		LED_7SEG_1 = ON;
		LED_7SEG_2 = ON;
		LED_7SEG_3 = ON;
		LED_7SEG_4 = ON;
		LED_7SEG_5 = OFF;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = ON;
		break;
	default:
		LED_7SEG_1 = OFF;
		LED_7SEG_2 = OFF;
		LED_7SEG_3 = OFF;
		LED_7SEG_4 = OFF;
		LED_7SEG_5 = OFF;
		LED_7SEG_6 = OFF;
		LED_7SEG_7 = OFF;
		break;
	}
}