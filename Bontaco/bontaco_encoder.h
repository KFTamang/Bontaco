#ifndef BONTACO_ENCODER_H
#define BONTACO_ENCODER_H

#include "iodefine.h"
#include "bontaco_common.h"

unsigned int get_encoder_count(Motor);
void reset_encoder_count(Motor);
void update_encoder_diff(Motor);
int get_encoder_diff(Motor);

#endif