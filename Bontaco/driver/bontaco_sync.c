#include "bontaco_sync.h"

int flag = 0;

void setFlag(void)
{
	flag = 1;
}

int getFlag(void)
{
	return flag;
}

void clearFlag(void)
{
	flag = 0;
}

void sync_1ms(void)
{
	// check if 1ms flag is already set, i.e. loop process is not in time!
	if (getFlag())
	{
		turn_on_debug_led(0);
		turn_on_debug_led(1);
		turn_on_debug_led(2);
	}
	// wait for 1ms flag to set
	while (!getFlag())
	{
	}
	clearFlag();
}