#include "bontaco_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi (3.14159265359)
#define MAX_ENCODER_COUNT (1024.0 * 30 / 8 * 1000 / 26 / Pi)

const float dt = 0.001;
float velocity = 0;
float acce = 0;
float a_velocity = 0;
float a_acce = 0;
float direction = 0;
float x = 0;
float y = 0;
float duty_right = 0;
float duty_left = 0;

void sync_1ms(void)
{
    static long count = 0;
    if (count > 10000)
    {
        exit(0);
    }
    else
    {
        count++;
    }
    acce = (duty_left + duty_right) / 2;
    // a_acce = duty_left - duty_right;
    velocity += dt * acce;
    a_velocity += dt * a_acce;
    direction += dt * a_velocity;
    x += dt * velocity * sin(direction);
    y += dt * velocity * cos(direction);

    printf("%f %f\n", x, y);
}

int main(void)
{
    Main();
}