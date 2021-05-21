/***********************************************************************/
/*                                                                     */
/*  FILE        :Bontaco.c                                             */
/*  DATE        :Sat, Nov 07, 2020                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :RX210                                                 */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.53).    */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
                  
#include "bontaco_init.h"
#include "bontaco_led.h"
#include "bontaco_test.h"
#include "bontaco_flag.h"


static void handleEvent(void);
static void constantProcess(void);
static void main_loop(void);
static void sync_1ms(void);
void Main(void);

static void initialization(void)
{
    turn_off_debug_led(0);
	turn_off_debug_led(1);
	turn_off_debug_led(2);
	turn_off_mode_led(0);	
	turn_off_mode_led(1);	

	display_7seg(10);

	// necessary to avoid weird rotation of left motor on enabling
	reset_encoder_count(LEFT);
	reset_encoder_count(RIGHT);

	check_battery();
	
	// test_debug_led();
	// test_mode_led();
	// test_display();
	// test_sci();
	// test_sensor();
	// test_battery_watch(); 
	// test_encoder();
	// test_motor();
	// test_run();
	// test_turn();
	// test_buzzer();

	// run_straight();
	run_straight_with_length(1000);
	// turn_90_degree(100, CW);
}

static void handleEvent(void)
{
	static int count = 0;
	if(count <9){
		count++;
	}else{
		sci_printf("r:%l\r\n", get_encoder_accumulated_count(RIGHT));
		sci_printf("l:%l\r\n", get_encoder_accumulated_count(LEFT));
		count = 0;
	}

	if(isEndOfMotion()){
		brake();
	}

}

static void constantProcess(void)
{
	update_encoder_diff(LEFT);
	update_encoder_diff(RIGHT);
	execute_current_motion();
	pid_control_velocity();
	pid_control_angular_velocity();
	increment_timer_ms();
	decrement_buzzer_timer();
	set_motor_duty_ratios();

}

static void main_loop(void)
{
	while(1){
		sync_1ms();

		handleEvent();

		constantProcess();
	}

}

static void sync_1ms(void)
{
	// check if 1ms flag is already set, i.e. loop process is not in time!
	if( getFlag() ){
		turn_on_debug_led(0);
		turn_on_debug_led(1);
		turn_on_debug_led(2);
	}
	// wait for 1ms flag to set
	while( !getFlag() );
	clearFlag();
}

void Main(void)
{
	initialization();

	main_loop();

}