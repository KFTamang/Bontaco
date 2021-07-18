#include "bontaco_util.h"

void check_battery()
{
	// check if battery has enough voltage
	// 2 cell LiPo battery should be 7.2V or greater.
	// Over-discharge can damege cells.
	int i;
	unsigned int volt = 0;
	for (i = 0; i < 5; i++)
	{
		// take average of 5 voltage measurement
		volt += measure_battery_voltage();
	}
	volt /= 5;
	if (volt <= 7200)
	{
		// going into stanby mode, telling user about low battery
		while (1)
		{
			turn_on_debug_led(0);
			for (i = 0; i < 1000000; i++)
			{
			}
			turn_off_debug_led(0);
			for (i = 0; i < 1000000; i++)
			{
			}
		}
	}
}