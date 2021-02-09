#include "bontaco_interrupt.h"
#include "bontaco_photosensor.h"
#include "bontaco_timer.h"

// this fuction is called 20us before mtu3_interruptB
void mtu3_interruptA(){
	
	static unsigned char counter = 0;
	
	switch(counter){
	case 0:
		turn_off_wall_led(counter);
		measure_sensor_value(counter);
		turn_on_wall_led(counter);
		break;
	case 1:
		turn_off_wall_led(counter);
		measure_sensor_value(counter);
		turn_on_wall_led(counter);
		break;
	case 2:
		turn_off_wall_led(counter);
		measure_sensor_value(counter);
		turn_on_wall_led(counter);
		break;
	case 3:
		turn_off_wall_led(counter);
		measure_sensor_value(counter);
		turn_on_wall_led(counter);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		counter = 0;
		return;
	default:
		break;
	}
	counter++;
}

// this fuction is called every 1/8 ms
void mtu3_interruptB(){
	
	static unsigned char counter = 0;
	
	switch(counter){
	case 0:
		measure_sensor_value(counter);
		turn_off_wall_led(counter);
		break;
	case 1:
		measure_sensor_value(counter);
		turn_off_wall_led(counter);
		break;
	case 2:
		measure_sensor_value(counter);
		turn_off_wall_led(counter);
		break;
	case 3:
		measure_sensor_value(counter);
		turn_off_wall_led(counter);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		counter = 0;
		increment_timer_ms();
		return;
	default:
		break;
	}
	counter++;
}
