#ifndef BONTACO_PHOTOSENSOR_H
#define BONTACO_PHOTOSENSOR_H

#include "../iodefine.h"

void measure_sensor_value(int);
unsigned int get_sensor_value(int);
void turn_on_wall_led(int);
void turn_off_wall_led(int);

#endif
