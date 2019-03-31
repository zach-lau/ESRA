#include "simpletools.h"
#include "servo.h"

enum HappyState{START, IM1, HAPPY}

enum HappyState happyState = START;

time_t initial_t;
time_t current_t;
int condition = 0;
int soundSense;

int happy(void){
	soundSense = input(5);
	switch(happyState){
		case START:
			servo_speed(12, 200);
			servo_speed(13, -200);
			pause(100);
			if (soundSense == 1){
				happyState = IM1;
			}
			break;

		case IM1:
			servo_speed(12,0);
			servo_speed(13,0);

			if (condition == 0){
				initial_t = time(NULL);
				condition = 1;
			} else {
				current_t = time(NULL);
				if (((double) (current_t) - (double) (initial_t)) >5) {
					condition = 0;
					happyState = HAPPY;
					break;
				}
			}
			pause(100);
			break;
		case HAPPY:
			if (condition == 0){
				initial_t = time(NULL);
				condition = 1;

			} else {
				current_t = time(NULL);
				if (((double) (current_t) - (double) (initial_t)) < 5){
					condition = 0;
					happyState = START;
				}
			}

			servo_speed(12, 255);
			servo_speed(13, 255);
			pause(100);

			break;
		default:
			happyState = START;
			break;
			;


	}
	return 0;
}