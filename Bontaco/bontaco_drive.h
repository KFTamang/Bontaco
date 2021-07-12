#include "iodefine.h"
#include "bontaco_common.h"
#include "bontaco_encoder.h"
#include "bontaco_battery_watch.h"

struct Motion
{
	unsigned int current_time_ms;
	unsigned int duration_ms;
	float acceralation;
	float ang_acceralation;
	long path_length;
	float initial_velocity;
	float initial_ang_velocity;
};

int enqueue(struct Motion motion);
int dequeue(void);
int queueIsEmpty(void);
int queueIsFull(void);
struct Motion getQueueTop(void);
struct Motion createMotionRunStraight(int length_mm);
struct Motion createMotion90turn(int radius_mm, Direction dir);
struct Motion createMotionWait(int wait_ms);
void setQueueTopToCurrentMotion(void);

void brake();
void set_target_velocity(float);
void set_target_angular_velocity(float);
void pid_control_motor_left();
void pid_control_motor_right();