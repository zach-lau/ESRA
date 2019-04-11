// Include necessary libraries
#include "simpletools.h"
#include "servo.h"

#define NOTE1 6
#define NOTE2 8
#define NOTE3 1

// Define note frequencies in 6th octave 
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

// Define note frequencies in 7th octave
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

// Define C note frequency in 8th octave
#define C8 4186.0

// Define note speeds
#define WHOLE 1000
#define HALF WHOLE/2
#define QUART WHOLE/4

// Enumerator to go between the 3 states
enum HappyState{START, IM1, HAPPY};

// Initialize enumerator to initial state
enum HappyState happyState = START;

// Initialize time variables to track time
time_t initial_t;
time_t current_t;

// Initialize conditions to assist in completing actions
int condition_h = 0;
int past_end = 0;

// Initialize sensor input
int soundSense;
int irSense;

int happy(void){
    soundSense = input(9);         //Set pin input to sensor variable                                                   
	switch(happyState){
	case START:
		servo_speed(12, 50);       //Adjust left servo speed
		servo_speed(13, -50);      //Adjust reight servo speed
        if (past_end == 1){        //Check if robot has just completed one full cycle
            pause(1000);
            past_end = 0;
        }          
		if (soundSense == 1)      //If sound input detected, go to next state
            happyState = IM1;      
		break;

	case IM1:
		servo_speed(12,0);
		servo_speed(13,0);
        pause(100);
        happybirthday();         //Call function to output song on buzzer
        happyState = HAPPY;      //Go to next state
		pause(100);
		break;
		
    case HAPPY:
        LED(7);                 //Call function to turn LED off
        servo_speed(12, 200);
    	servo_speed(13, 200);
    	if (condition_h == 0){ 
    		initial_t = time(NULL); //Set initial time
    		condition_h = 1;
    	} else {
    		current_t = time(NULL); //Retrieve current time
    		if (((double) (current_t) - (double) (initial_t)) > 5){ //Check if elapsed time is greater than 5s
    			condition_h = 0;
                past_end = 1;
    			happyState = START;  //Return to initial state
    		}
    	}
    	servo_speed(12, 255);
    	servo_speed(13, 255);
    	pause(100);
        LED(1);                 //Call function to turn on green LED
        pause(100);
    	break;

	default:
		happyState = START;
		break;
		;
	}
	return 0;
}

//Function to play happy birthday on output buzzer
void happybirthday(){
    freqout(NOTE1, QUART, D6);
    pause(100);
    freqout(NOTE1, QUART, D6);
    pause(100);
    freqout(NOTE1, HALF, E6);
    pause(100);
    freqout(NOTE1, HALF, D6);
    pause(100);
    freqout(NOTE1, HALF, G6);
    pause(100);
    freqout(NOTE1, WHOLE, F6S);
    pause(100);
    freqout(NOTE1, QUART, D6);
    pause(100);
    freqout(NOTE1, QUART, D6);
    pause(100);
    freqout(NOTE1, HALF, E6);
    pause(100);
    freqout(NOTE1, HALF, D6);
    pause(100);
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

//Function to control LED color
void LED(int x){
    if (x == 0){        //Turn LED red
        high(0);
        low(1);
        low(2);
    }    
    if (x == 1){        //Turn LED green
        low(0);
        high(1);
        low(2);
    }    
    if (x == 2){        //Turn LED blue
        low(0);
        low(1);
        high(2);
    }    
    if (x == 3){        //Turn LED yellow
        high(0);
        high(1);
        low(2);
    }    
    if (x == 4){        //Turn LED magenta
        high(0);
        low(1);
        high(2);
    }    
    if (x == 5){        //Turn LED cyan
        low(0);
        high(1);
        high(2);
    }    
    if (x == 6){        //Turn LED white
        high(0);
        high(1);
        high(2);
    }  
    if (x == 7){        //Turn LED off
        low(0);
        low(1);
        low(2);
    }
} 
