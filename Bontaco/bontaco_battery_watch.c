#include "bontaco_battery_watch.h"

#define BATTERY_VOLTAGE ((1 << 4))

#define ADC_BUSY (S12AD.ADCSR.BIT.ADST)
#define ADC_SELECT (S12AD.ADANSA.WORD)

#define ADC_VALUE (S12AD.ADDR4)


unsigned int measure_battery_voltage(){
	// wait until ADC module is ready
	while(ADC_BUSY != 0);
	
	// select which pin to do ADC operation
	ADC_SELECT = BATTERY_VOLTAGE;
	
	// start AD conversion
	ADC_BUSY = 1;
	
	// wait for ADC to finish
	while(ADC_BUSY != 0);
	
	// return battery voltage in mV
	// battery voltage (mV): ADC_VALUE(12bit) * 5000mV / 4096 * 12.7kOhm/2.7kOhm
	return 5000*127*ADC_VALUE/4096/27;
	
}