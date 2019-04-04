#include "simpletools.h"                      
#include "servo.h"

enum SadState{START, MID, SAD};

enum SadState sadState = START;

int irSense;
int soundSense; 

time_t initial_t;
time_t current_t;

int sad(void){
  freqout(10, 1, 38000);
  freqout(14, 1, 38000);
  irSense = input(11);

  switch(sadState){
    case START:
      
      break;
      
    case MID:
    
      break;
      
    case SAD:          
      
      break;
        
    default:
      sadState = START;
      break;
  }    
  return 0;
}

