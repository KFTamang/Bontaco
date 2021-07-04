DRIVERS = bontaco_battery_watch.c  bontaco_buzzer.c  bontaco_encoder.c  bontaco_init.c  bontaco_interrupt.c  bontaco_led.c  bontaco_motor_pwm.c  bontaco_photosensor.c  bontaco_sync.c  bontaco_util.c
SRCS = bontaco_main.c bontaco_drive.c bontaco_timer.c sim.c $(DRIVERS)
OBJS = $(SRCS:%.c=%.o)
INCLUDE = -I../header -I..
LIB = -lm
FLAGS = -g -Wall -Wextra


all:$(OBJS)
	gcc $(FLAGS) $(INCLUDE) $(OBJS) -o sim $(LIB)

run:all
	./sim

bontaco_main.o:../bontaco_main.c
	gcc $(FLAGS) $(INCLUDE) -c $<

bontaco_drive.o:../bontaco_drive.c
	gcc $(FLAGS) $(INCLUDE) -c $<

bontaco_timer.o:../bontaco_timer.c
	gcc $(FLAGS) $(INCLUDE) -c $<

%.o: %.c
	gcc $(FLAGS) $(INCLUDE) -c $^

clean:
	rm *.o sim