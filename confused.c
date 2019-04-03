#include "simpletools.h"
#include "servo.h"
#include "adcDCpropab.h"
#include "mx2125.h" 
enum ConfusedState{START, SHAKEN, CONFUSED1, CONFUSED2, RECOVERING};

enum ConfusedState confusedState = START;

int x;
int y;

time_t timer_t;
time_t initial_t;
time_t current_t;
float vol;
int timer_c = 0;
int condition_s = 0;
int condition_t = 0;

int confused(){
	x=mx_accel(3);
	y=mx_accel(4);
	switch(confusedState){
		case START:                                   // Repeat indefinitely
		servo_speed(12, 30)
		servo_speed(13, 30)
		pause(100);        		// 1/5th second before repeat
		for(int i=0;i<5,i++){
		if((x>300)||(y>300)){
			high(buzzer)
			i++;
			pause(1000)
		}
		}
		if(i=5){
		confusedState=CONFUSED1;
		}
		break;
		
		case CONFUSED1:
		high(buzzer)
		
  }  
  }
