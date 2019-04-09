#include "simpletools.h"                      
#include "servo.h"

//enumerator to go between the 4 states
enum LethargicState{START, STRD1, STRD2, TRD};

//initializing the enumerator to the initial state
enum LethargicState lethargicState = START;

//initializing the IR sensor
int irSense;
//initializing the sound sensor
int soundSense;

//Initializing the time variables to 
//determine how much time as passed
time_t initial_t;
time_t current_t;

//condition to help complete actions when 
//entering a state for the first time
int condition_l = 0;

int lethargic(void){
  freqout(10, 1, 38000); //sending out a signal for the ultrasonic sensors
  irSense = input(11); //checking to see if the signal was recieved back
  
  switch(lethargicState){
    
    case START:
      LED(7);          //turns off LED
      servo_speed(12, 50); //Robot moves slowly
      servo_speed(13, 50);
      if (condition_l == 0){ //if this is the first time entering the state
        initial_t = time(NULL); //time when first entered this state
        condition_l = 1;        
      } else {
        current_t = time(NULL); 
        if (((double) (current_t) - (double) (initial_t)) > 2){
          condition_l = 0;        //resets condition
          lethargicState = STRD1; //jumps to next state
        }          
      }          
      break;
    
      case STRD1:
      LED(7);
      servo_speed(12, 20); //robot moves very slowly
      servo_speed(13, 20);
      
      if (condition_l == 0){ //if this is the first time entering the state
        initial_t = time(NULL); //time when first entered this state
        condition_l = 1;        
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 2){
          condition_l = 0;        //resets condition
          lethargicState = STRD2; //jumps to next state
        }          
      }   
      //if there is input the led blinks and 
      //robot returns to the initial state
      if (irSense != 1){     
        LED(3);
        pause(100);
        LED(7);
        lethargicState = START;
      } 
      if (soundSense == 1){
        LED(3);
        pause(100);
        LED(7);
        lethargicState = START;
      } 
      break;
      
    case STRD2:
    LED(7);
      servo_speed(12, 10);  //robot moves even slower
      servo_speed(13, 10);
      
      if (condition_l == 0){ //if this is the first time entering the state
        initial_t = time(NULL); //time when first entered this state
        condition_l = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 2){
          condition_l = 0;       //resets condition
          lethargicState = TRD;  //jumps to next state
        }          
      }   
      //if there is input the led blinks and 
      //robot returns to the initial state
      
      if (irSense != 1){
        LED(3);
        pause(100);
        LED(7);
        lethargicState = START;
      } 
      if (soundSense == 1){
        LED(3);
        pause(100);
        LED(7);
        lethargicState = START;
      } 
      break;
      
    case TRD:  
    LED(7);        
      servo_speed(12, 0); //robot stops moving
      servo_speed(13, 0);
      
      //if there is input the led blinks and 
      //robot returns to the initial state
      if (irSense != 1){
        LED(3);
        pause(100);
        LED(7);
        lethargicState = START;
      } 
      break;
      
    default:
      lethargicState = START;
      break;
  }    
  return 0;
}

