#include "simpletools.h"
#include "servo.h"
#define NOTE1 11
#define NOTE2 8
#define NOTE3 1


#define C6 1046.5
#define C6S 1108.7
#define D6  1174.7
#define D6S 1244.5
#define E6 1318.5
#define F6 1396.9
#define F6S 1480.0
#define G6 1568.0
#define G6S 1661.2
#define A6 1760.0
#define A6S 1864.7
#define B6 1975.5

#define C7 2093.0
#define C7S 2217.5
#define D7  2349.3
#define D7S 2489.0
#define E7 2367.0
#define F7 2793.9
#define F7S 2960.0
#define G7 3136.0
#define G7S 3322.4
#define A7 3520.0
#define A7S 3729.3
#define B7 3951.1

#define C8 4186.0

#define WHOLE 1000
#define HALF WHOLE/2
#define QUART WHOLE/4
enum HappyState{START, IM1, HAPPY};

enum HappyState happyState = START;

time_t initial_t;
time_t current_t;
int condition_h = 0;
int soundSense;
int irSense;

int happy(void){
	soundSense = input(5);
	switch(happyState){
		case START:
			servo_speed(12, 50);
			servo_speed(13, -50);
			if (soundSense == 1/){
		      happyState = IM1;
			}      
			break;

		case IM1:
			servo_speed(12,0);
			servo_speed(13,0);
       pause(100);
       happybirthday();
       happyState = HAPPY;
			pause(100);
			break;
		case HAPPY:
       low(1);
       servo_speed(12, 200);
			servo_speed(13, 200);
			if (condition_h == 0){
				initial_t = time(NULL);
				condition_h = 1;

			} else {
				current_t = time(NULL);
				if (((double) (current_t) - (double) (initial_t)) > 5){
					condition_h = 0;
					happyState = START;
				}
			}
			servo_speed(12, 255);
			servo_speed(13, 255);
			pause(100);
       high(1);
       pause(100);
			break;
		default:
			happyState = START;
			break;
			;
	}
	return 0;
}

void happybirthday(){
  freqout(NOTE1, QUART, D6);
  pause(100);
  LED(0);
  freqout(NOTE1, QUART, D6);
  pause(100);
  LED(1);
  freqout(NOTE1, HALF, E6);
  pause(100);
  LED(2);
  freqout(NOTE1, HALF, D6);
  pause(100);
  LED(3);
  freqout(NOTE1, HALF, G6);
  pause(100);
  LED(4);
  freqout(NOTE1, WHOLE, F6S);
  pause(100);
  LED(5);
  freqout(NOTE1, QUART, D6);
  pause(100);
  LED(6);
  freqout(NOTE1, QUART, D6);
  pause(100);
  LED(5);
  freqout(NOTE1, HALF, E6);
  pause(100);
  LED(4);
  freqout(NOTE1, HALF, D6);
  pause(100);
  LED(3);
  freqout(NOTE1, HALF, A6);
  pause(100);
  LED(2);
  freqout(NOTE1, WHOLE, G6);
  pause(100);
  LED(1);
  freqout(NOTE1, QUART, D6);
  pause(100);
  freqout(NOTE1, QUART, D6);
  pause(100);
  freqout(NOTE1, HALF, D7);
  pause(100);
  freqout(NOTE1, HALF, B6);
  pause(100);
  freqout(NOTE1, HALF, G6);
  pause(100);
  freqout(NOTE1, HALF, F6S);
  pause(100);
  freqout(NOTE1, HALF, E6);
  pause(100);
  freqout(NOTE1, QUART, C7);
  pause(100);
  freqout(NOTE1, QUART, C7);
  pause(100);
  freqout(NOTE1, HALF, B6);
  pause(100);
  freqout(NOTE1, HALF, G6);
  pause(100);
  freqout(NOTE1, HALF, A6);
  pause(100);
  freqout(NOTE1, WHOLE, G6);
  pause(100);
  
}

void LED(int x){
  if (x == 0){
    high(0);
    low(1);
    low(2);
  }    
  if (x == 1){
    low(0);
    high(1);
    low(2);
  }    
  if (x == 2){
    low(0);
    low(1);
    high(2);
  }    
  if (x == 3){
    high(0);
    high(1);
    low(2);
  }    
  if (x == 4){
    high(0);
    low(1);
    high(2);
  }    
  if (x == 5){
    low(0);
    high(1);
    high(2);
  }    
  if (x == 6){
    high(0);
    high(1);
    high(2);
  }  
}  
