#include "bontaco_photosensor.h"
#include "bontaco_led.h"

#define SENSOR0 (0x01)
#define SENSOR1 (0x02)
#define SENSOR2 (0x04)
#define SENSOR3 (0x08)

#define SENSOR_BUSY (S12AD.ADCSR.BIT.ADST)
#define SENSOR_SELECT (S12AD.ADANSA.WORD)

#define SENSOR_VALUE0 (S12AD.ADDR0)
#define SENSOR_VALUE1 (S12AD.ADDR1)
#define SENSOR_VALUE2 (S12AD.ADDR2)
#define SENSOR_VALUE3 (S12AD.ADDR3)


#define ON (0)
#define OFF (1)

#define WALL_LED_0 (PORTH.PODR.BIT.B0)
#define WALL_LED_1 (PORTH.PODR.BIT.B1)
#define WALL_LED_2 (PORTH.PODR.BIT.B2)
#define WALL_LED_3 (PORTH.PODR.BIT.B3)

// global array to store sensor values, limited inside this compile unit
static unsigned int sen_val[4] = {11,22,33,44};

unsigned int get_sensor_value(int sensor_num){
	if(sensor_num < 0 || sensor_num > 3){
		return 1919;
	}
	return sen_val[sensor_num];
}

unsigned int select_sensor(int sensor_num){
	switch(sensor_num){
	case 0:
		return 0x01;
	case 1:
		return 0x02;
	case 2:
		return 0x04;
	case 3:
		return 0x08;
	}
	return 0;
}

unsigned int read_adc_register(int sensor_num){
	switch(sensor_num){
	case 0:
		return S12AD.ADDR0;
	case 1:
		return S12AD.ADDR1;
	case 2:
		return S12AD.ADDR2;
	case 3:
		return S12AD.ADDR3;
	}
	return 0;
}

void measure_sensor_value(int sensor_num){	
	if(sensor_num < 0 || sensor_num > 3){
		return;
	}
	// wait until ADC module is ready
	while(SENSOR_BUSY != 0);
	
	// select which pin to do ADC operation
	SENSOR_SELECT = select_sensor(sensor_num);
	
	// start AD conversion
	SENSOR_BUSY = 1;
	
	// wait for ADC to finish
	while(SENSOR_BUSY != 0);
	
	// store ADC value to a static array
	sen_val[sensor_num] = read_adc_register(sensor_num);
}

void turn_on_wall_led(int i){
	switch(i){
	case 0:
		WALL_LED_0 = ON;
		break;		
	case 1:
		WALL_LED_1 = ON;
		break;		
	case 2:
		WALL_LED_2 = ON;
		break;		
	case 3:
		WALL_LED_3 = ON;
		break;
	default:
		break;
	}
}

void turn_off_wall_led(int i){
	switch(i){
	case 0:
		WALL_LED_0 = OFF;
		break;		
	case 1:
		WALL_LED_1 = OFF;
		break;		
	case 2:
		WALL_LED_2 = OFF;
		break;		
	case 3:
		WALL_LED_3 = OFF;
		break;
	default:
		break;
	}
}