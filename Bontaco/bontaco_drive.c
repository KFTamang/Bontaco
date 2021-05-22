#include "bontaco_drive.h"
#include "bontaco_led.h"

#define Pi (3.1415)
#define VELOCITY_LOW (200) // [mm/sec], speed of exploration
#define VELOCITY_MIDDLE (1000) // [mm/sec], speed of exploration
#define mV_PER_VELOCITY (60.0*0.470/(8.0/30.0)/Pi/25.0) //1.34649 [mV / (mm/sec)]
#define mV_PER_ANGULAR_V (mV_PER_VELOCITY*75.0*Pi/180.0) // 1.7625 [mV / (deg/sec)]
#define mm_PER_COUNT_RIGHT (1000.0/46422.0) // distance per encoder count in mm based on mesurement 
#define mm_PER_COUNT_LEFT (1000.0/44369.0) // distance per encoder count in mm based on mesurement 
#define deg_PER_COUNT_RIGHT (mm_PER_COUNT_RIGHT*180.0/Pi/75.0) // degree per encoder count difference (i.e. LEFT - RIGHT)
#define deg_PER_COUNT_LEFT (mm_PER_COUNT_LEFT*180.0/Pi/75.0) // degree per encoder count difference (i.e. LEFT - RIGHT)
#define PERIOD (0.001) // time period of drive control, 1ms
#define Kp_V (0.001 ) // velocity coefficient for P control
#define Ki_V (0.001 ) // velocity coefficient for I control
#define Kp_AV  (0.0001 ) // angular velocity coefficient for P control
#define Ki_AV  (0.001 ) // angular velocity coefficient for I control

static float target_velocity = 0;
static float target_angular_velocity = 0;
static float dutyratio_v = 0;
static float dutyratio_av = 0;
static float integral_velocity = 0;
static float integral_av = 0;


long get_path_length(void);


struct Motion current_motion = {0,0,0,0,0,0};
struct Motion createMotion( unsigned int, float, float, long, float, float);
static void reset_path_length(void);

#define QUEUE_MAX (10)
struct MotionQueue{
    char start;
    char item_num;
    struct Motion array[QUEUE_MAX];
} motionQueue = {0, 0};

int queueIsEmpty(void)
{
    return (motionQueue.item_num == 0);
}

int queueIsFull(void)
{
    return (motionQueue.item_num == QUEUE_MAX - 1);
}

int enqueue(struct Motion motion)
{
    int pos;
    if(!queueIsFull()){
        pos = (motionQueue.start + motionQueue.item_num ) % QUEUE_MAX;
        motionQueue.array[pos] = motion;
        motionQueue.item_num++;
        return 1;
    }else{
        return 0;
    }
}

int dequeue(void)
{
    if(!queueIsEmpty()){
        motionQueue.start++;
        motionQueue.start %= QUEUE_MAX;
        motionQueue.item_num--;
        return 1;
    }else{
        return 0;
    }
}

struct Motion getQueueTop(void)
{
    if(!queueIsEmpty()){
        return motionQueue.array[motionQueue.start];
    }else{
        return createMotion(0,0,0,0,0,0);
    }
}

void setQueueTopToCurrentMotion(void)
{
    current_motion = getQueueTop();
}

struct Motion createMotion(
	unsigned int _duration_ms,
	float _acceralation,
	float _ang_acceralation,
	long _path_length,
	float _initial_velocity,
	float _initial_ang_velocity)
{
    struct Motion new;
    new.current_time_ms      = 0;
	new.duration_ms          = _duration_ms;
	new.acceralation         = _acceralation;
	new.ang_acceralation     = _ang_acceralation;
	new.path_length          = _path_length;
	new.initial_velocity     = _initial_velocity;
	new.initial_ang_velocity = _initial_ang_velocity;
    return new;
}

int isEndOfMotion(void)
{
    return (current_motion.current_time_ms >= current_motion.duration_ms || current_motion.path_length <= get_path_length());
}

void execute_current_motion(void)
{
    if(current_motion.current_time_ms == 0){
        target_velocity = current_motion.initial_velocity;
        target_angular_velocity = current_motion.initial_ang_velocity;
        reset_path_length();
    }else{
        target_velocity += current_motion.acceralation;
        target_angular_velocity += current_motion.ang_acceralation;
    }
    current_motion.current_time_ms++;
}

struct Motion createMotionRunStraight(int length_mm)
{
    return createMotion(10000, 0, 0, length_mm, VELOCITY_LOW, 0);
}

struct Motion createMotion90turn(int radius_mm, Direction dir)
{
    float duration_ms = 1000.0 * radius_mm * Pi / 2 / VELOCITY_LOW;
    float _target_av = 90.0 * 1000.0 / duration_ms;
    int length_mm = radius_mm * Pi / 2;
    if(dir == CCW){
        _target_av *= -1;
    }
    return createMotion(10000, 0, 0, length_mm, VELOCITY_LOW, _target_av);
}

struct Motion createMotionWait(int wait_ms)
{
    return createMotion(wait_ms, 0, 0, 10000, 0, 0);
}

static float get_velocity(void)
{
    int count_right = get_encoder_diff(RIGHT);
    int count_left  = get_encoder_diff(LEFT);
    float velocity = (mm_PER_COUNT_RIGHT * count_right + mm_PER_COUNT_LEFT * count_left) / 2 / PERIOD;
    return velocity;
}

// angular velocity, + for clockwise, - for counter-clockwise
static float get_angular_velocity(void)
{
    int count_right = get_encoder_diff(RIGHT);
    int count_left  = get_encoder_diff(LEFT);
    float angular_velocity = (deg_PER_COUNT_LEFT * count_left - deg_PER_COUNT_RIGHT * count_right) / PERIOD;
    return angular_velocity;
}

long get_path_length(void)
{
    long count_right = get_encoder_accumulated_count(RIGHT);
    long count_left = get_encoder_accumulated_count(LEFT);
    long path_length = 0;
    path_length = count_right * mm_PER_COUNT_RIGHT + count_left * mm_PER_COUNT_LEFT;
    path_length /= 2;
    return path_length;
}

static void reset_path_length(void)
{
    reset_encoder_accumulated_count();
}

static void reset_velocity_parameters(void)
{
    dutyratio_v = 0;
    dutyratio_av = 0;
    integral_velocity = 0;
    integral_av = 0;
}

void brake(void)
{
    reset_velocity_parameters();
    set_target_velocity(0);
    set_target_angular_velocity(0);
    current_motion = createMotion(0,0,0,0,0,0);
    enable_motors();
}

void set_target_velocity(float _target_velocity)
{
    target_velocity = _target_velocity;
}

void set_target_angular_velocity(float _target_a_velocity)
{
    target_angular_velocity = _target_a_velocity;
}

void set_motor_duty_ratios(void)
{
    float dutyratio_left = dutyratio_v + dutyratio_av/2;
    float dutyratio_right = dutyratio_v - dutyratio_av/2;
    set_duty_ratio(RIGHT, dutyratio_right);
    set_duty_ratio(LEFT, dutyratio_left);
}

void pid_control_velocity(void)
{
    float target_duty_ratio = mV_PER_VELOCITY * target_velocity / measure_battery_voltage();
    float current_velocity = get_velocity();
    float residue_velocity = target_velocity - current_velocity;
    float pid_duty_ratio = 0;
    // Integral
    integral_velocity += residue_velocity;
    // PID output
    pid_duty_ratio = residue_velocity * Kp_V;
    pid_duty_ratio += integral_velocity * Ki_V;

    dutyratio_v = target_duty_ratio + pid_duty_ratio;
}

void pid_control_angular_velocity(void)
{
    float target_duty_ratio = mV_PER_ANGULAR_V * target_angular_velocity / measure_battery_voltage();
    float current_av = get_angular_velocity();
    float residue_av = target_angular_velocity - current_av;
    float pid_duty_ratio = 0;
    // Integral
    integral_av += residue_av;
    // PID output
    pid_duty_ratio = residue_av * Kp_AV;
    pid_duty_ratio += integral_av * Ki_AV;

    dutyratio_av = target_duty_ratio + pid_duty_ratio;
}