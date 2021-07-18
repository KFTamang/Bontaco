#ifndef BONTACO_TEST_H
#define BONTACO_TEST_H

#include "bontaco_led.h"
#include "bontaco_sci.h"
#include "bontaco_photosensor.h"
#include "bontaco_timer.h"
#include "bontaco_battery_watch.h"
#include "bontaco_encoder.h"
#include "bontaco_motor_pwm.h"
#include "bontaco_buzzer.h"

void test_debug_led();
void test_mode_led();
void test_display();
void test_sci();
void test_sensor();
void test_battery_watch();
void test_encoder();
void test_motor();
void test_run();
void test_buzzer();
void test_turn();

#endif