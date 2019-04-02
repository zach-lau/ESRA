#include "simpletools.h"
#include "servo.h"
#include "adcDCpropab.h"

enum ScaredState{START, SK1, SK2, SCRD};

enum ScaredState scaredState = START;

int irSense;

time_t timer_t;
time_t initial_t;
time_t current_t;
float vol;
int timer_c = 0;
int condition_s = 0;
int condition_t = 0;

int scared(void){
  freqout(6, 1, 38000);
  freqout(8, 1, 38000);
  irSense = input(7);
  adc_init(21, 20, 19, 18);
  switch(scaredState){
    
    case START:
    condition_t = 0;
    low(26);
    low(27);
    servo_speed(12, 30);
    servo_speed(13, -30);
    pause(100);
    vol = adc_volts(2);
    if (vol < 0.8){           
      scaredState = SK1;
    }      
    break;
    
    
    case SK1:
    high(26);
    low(27);
    servo_speed(12, 100);
    servo_speed(13, 100);
      if (condition_t == 0){
        print("*");
        timer_t = time(NULL);
        condition_t = 1;
      } else {
        print("^");
        current_t = time(NULL);
        if (((double)(current_t) - (double)(timer_t)) > 6){
          scaredState = START;
          condition_t = 0;
       }        
      }        
      if (condition_s == 0){
        initial_t = time(NULL); //time when first entered SK1
        condition_s = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 0.25){
          //occues if 0.5 seconds ahve passed
          condition_s = 0;
          scaredState = SK2;
        }          
      } 
    if (irSense == 0){
      scaredState = SCRD;
      break;
    }      
    
    break;
    
    
    case SK2:
    condition_t = 1;
    high(27);
    low(26);
    servo_speed(12, -100);
    servo_speed(13, -100);
      if (condition_s == 0){
        initial_t = time(NULL); //time when first entered SK1
        condition_s = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 0.25){
          //occurs if 0.5 seconds ahve passed
          condition_s = 0;
          scaredState = SK1;
        }          
      } 
    if (irSense == 0){
      scaredState = SCRD;
      break;
    }      
    
    break;
    
    
    case SCRD:
    high(26);
    high(27);
      if (condition_s == 0){
        initial_t = time(NULL); //time when first entered MAD
        condition_s = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 4){
          //occues if 4 seconds have passed
          condition_s = 0;
          scaredState = START;
        }          
      }
      servo_speed(12, 200);
      servo_speed(13, -200);
      break;
  }    
}  
