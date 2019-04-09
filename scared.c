#include "simpletools.h"
#include "servo.h"
#include "adcDCpropab.h"

//enumerator to go between the 4 states
enum ScaredState{START, SK1, SK2, SCRD};

//initializing the enumerator to the initial state
enum ScaredState scaredState = START;

//initializing the irSense
int irSense;

//Initializing the time variables to 
//determine how much time as passed
time_t timer_t;
time_t initial_t;
time_t current_t;

//initializing the phototransister input
float vol;

//conditions to help complete actions when 
//entering a state for the first time
int timer_c = 0;
int condition_s = 0;
int condition_t = 0;

int scared(void){
  freqout(10, 1, 38000); //sending out a signal for the ultrasonic sensors
  irSense = input(11); //checking to see if the signal was recieved back
  adc_init(21, 20, 19, 18); //initializing the A to D pinin
  
  switch(scaredState){
	  
    case START:
    condition_t = 0;        //resets condition
    LED(7);					     //turns off LED
    servo_speed(12, -30);   //robot backs away slowly
    servo_speed(13, 30);
    pause(100);
    vol = adc_volts(3);      //checks the phototransister voltage drop
    if (vol < 0.01){         //if low light then the robot starts shaking
      scaredState = SK1;
    }      
    break;
    
    
    case SK1:
    LED(6);                 //white light turns on
    servo_speed(12, 100);   // robot turns right quickly
    servo_speed(13, 100);
      if (condition_t == 0){ //condition_t is used to enter the 
							           //initial state after the robot calms down
        timer_t = time(NULL);
        condition_t = 1;
      } else {
        current_t = time(NULL);
        if (((double)(current_t) - (double)(timer_t)) > 6){
          scaredState = START;
          condition_t = 0;
       }        
      }        
	  
      if (condition_s == 0){   //condition_s is used to alternate between
							   //SK1 and SK2
        initial_t = time(NULL); 
        condition_s = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 0.25){
          //occues if 0.25 seconds have passed
          condition_s = 0;
          scaredState = SK2;
        }          
      } 
    if (irSense != 1){ //if a hand comes closer the robot becomes scared
      scaredState = SCRD;
      break;
    }      
    
    break;
    
    
    case SK2:
    condition_t = 1;  //resets the condition to enter the initial state
    servo_speed(12, -100); //robot turns left quickly
    servo_speed(13, -100);
      if (condition_s == 0){
        initial_t = time(NULL); //time when first entered SK1
        condition_s = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 0.25){
          //occurs if 0.25 seconds have passed
          condition_s = 0;
          scaredState = SK1;
        }          
      } 
    if (irSense != 1){ //if a hand comes closer the robot becomes scared
      scaredState = SCRD;
      break;
    }      
    
    break;
    
    
    case SCRD:
      if (condition_s == 0){ 
        initial_t = time(NULL); //time when first entered MAD
        condition_s = 1;        
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 4){
          //occurs if 4 seconds have passed
          condition_s = 0;
          scaredState = START;
        }          
      }
      servo_speed(12, -200);   //Robot backs away quickly
      servo_speed(13, 200);
      LED(7);                  //LED blinks
      pause(500);
      LED(6);
      break;
  }    
}  

