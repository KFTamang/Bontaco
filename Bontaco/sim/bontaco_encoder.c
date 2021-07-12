#include "bontaco_encoder.h"

#define Pi (3.14159265359)
#define MAX_ENCODER_COUNT (1024.0 * 30 / 8 * 1000 / 26 / Pi)

extern const double dt;
extern double velocity;
extern double acce;
extern double a_velocity;
extern double a_acce;
extern double direction;
extern double x;
extern double y;
extern double duty_right;
extern double duty_left;

static long count_right = 0;
static long count_left = 0;
static long count_right_diff = 0;
static long count_left_diff = 0;

unsigned int get_encoder_count(Motor motor)
{
    if (motor == RIGHT)
    {
        return count_right;
    }
    else if (motor == LEFT)
    {
        return count_left;
    }
    else
    {
        return 0;
    }
}

long get_encoder_accumulated_count(Motor motor)
{
    if (motor == RIGHT)
    {
        return count_right;
    }
    else if (motor == LEFT)
    {
        return count_left;
    }
    else
    {
        return 0;
    }
}

void reset_encoder_accumulated_count()
{
    count_right = 0;
    count_left = 0;
}

void reset_encoder_count(Motor motor)
{
    count_right = 0;
    count_left = 0;
    count_right_diff = 0;
    count_left_diff = 0;
}

void update_encoder_diff(Motor motor)
{
    if (motor == RIGHT)
    {
        count_right_diff = duty_right * MAX_ENCODER_COUNT;
        count_right += count_right_diff;
    }
    else if (motor == LEFT)
    {
        count_left_diff = duty_left * MAX_ENCODER_COUNT;
        count_left += count_left_diff;
    }
    else
    {
        return 0;
    }
}

int get_encoder_diff(Motor motor)
{
    if (motor == RIGHT)
    {
        return count_right_diff;
    }
    else if (motor == LEFT)
    {
        return count_left_diff;
    }
    else
    {
        return 0;
    }
}
