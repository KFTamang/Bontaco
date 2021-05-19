#include "bontaco_interrupt.h"
#include "bontaco_flag.h"

// this fuction is called 20us before mtu3_interruptB
void mtu3_interruptA(){
	static unsigned char counter = 0;
	if( counter < 4){
		turn_off_wall_led(counter);
		measure_sensor_value(counter);
		turn_on_wall_led(counter);
	}
	
	if( counter >= 7){
		counter = 0;
	}else{
		counter++;
	}

}

// this fuction is called every 1/8 ms
void mtu3_interruptB(){
	static unsigned char counter = 0;
	if( counter < 4){
		measure_sensor_value(counter);
		turn_off_wall_led(counter);
	}
	if( counter >= 7){
		counter = 0;
		setFlag();
	}else{
		counter++;
	}
}
