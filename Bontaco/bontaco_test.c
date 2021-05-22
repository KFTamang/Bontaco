#include "bontaco_test.h"

void test_debug_led(){
	int i;
	
	turn_on_debug_led(0);
	turn_off_debug_led(1);
	turn_off_debug_led(2);
	for(i=0;i<2000000;i++);
	turn_off_debug_led(0);
	turn_on_debug_led(1);
	turn_off_debug_led(2);
	for(i=0;i<2000000;i++);
	turn_off_debug_led(0);
	turn_off_debug_led(1);
	turn_on_debug_led(2);
	for(i=0;i<2000000;i++);
	
	turn_on_debug_led(0);
	turn_on_debug_led(1);
	turn_on_debug_led(2);

	
	for(i=0;i<2000000;i++);	
	
	turn_off_debug_led(0);
	turn_off_debug_led(1);
	turn_off_debug_led(2);
}

void test_mode_led(){
	int i;
	turn_on_mode_led(0);	
	turn_off_mode_led(1);	
	for(i=0;i<2000000;i++);	
	turn_off_mode_led(0);	
	turn_on_mode_led(1);	
	for(i=0;i<2000000;i++);	
	turn_off_mode_led(0);	
	turn_off_mode_led(1);
}


void test_display(){
	int i,j;
	for(i=0;i<1000;i++){
		display_7seg((int)get_timer_sec()%10);
		for(j=0;j<20000;j++);
	}
	// turn off 7seg
	display_7seg(10);	
	
}

void test_sci(){
	unsigned int i = 0;
	for(i=0;i<500;i++){
		sci_printf("SCI test count %u\r\n", i);
		sci_printf("%u %u\r\n", get_timer_sec(), get_timer_ms());
	}		
}

void test_sensor(){
	int i,k,m;
	int sensor_value;
	for(i=0;i<100;i++){
		for(k=0;k<4;k++){
			sensor_value = (int)get_sensor_value(k);
			sci_printf("%d:%d, ", k, sensor_value);
			for(m=0;m<1000000;m++);
		}
		sci_printf("\r\n");
	}
	
}

void test_battery_watch(){
	int i,m;
	for(i=0;i<100;i++){
		display_7seg(i%10);
		sci_printf("Battery voltage(mV):%u\r\n", measure_battery_voltage());
		for(m=0;m<100000;m++);
	}	
	
}

void test_encoder(){
	int i;
	for(i=0;i<1000;i++){
		sci_printf("Encoder right:%d\r\n", get_encoder_diff(RIGHT));
		sci_printf("Encoder left:%d\r\n", get_encoder_diff(LEFT));
		sci_printf("Encoder accumulate right:%l\r\n", get_encoder_accumulated_count(RIGHT));
		sci_printf("Encoder accumulate left:%l\r\n", get_encoder_accumulated_count(LEFT));
		wait_ms(100);
	}	
	
}

void test_motor(){
}

void test_run(){
}

void test_turn(){
}

void test_buzzer(){
	int m;
	for(m=0;m<50;m++){
		turn_on_debug_led(0);
		ring_buzzer_for_ms(10);
		turn_on_debug_led(1);
		wait_ms(500);
		wait_sec(1);
		turn_off_debug_led(0);
		turn_off_debug_led(1);
	}
}
