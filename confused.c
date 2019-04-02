#include "simpletools.h"                      
#include "servo.h"
#include "adcDCpropab.h"

enum ScaredState{START, SK1, SK2, SCRD};

enum ScaredState scaredState = START;

time_t timer_t;
time_t initial_t;
time_t current_t;
int timer_c = 0;
int condition = 0;

int scared(void){
  float vol;
  irSense = input(7);
  switch(scaredState){
    
    case START:
    servo_speed(12, 50);
    servo_speed(13, -50);
    pause(100);
    vol = adc_volts(2);
    if (vol < 5){           //TEMP VALUES-MUST BE CHANGED THROUGH TESTING
      scaredState = SK1;
    }      
    break;
    
    
    case SK1:
      if (condition == 0){
        initial_t = time(NULL); //time when first entered SK1
        condition = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 0.5){
          //occues if 0.5 seconds ahve passed
          condition = 0;
          scaredState = SK2;
        }          
      } 
    if (irSense == 1){
      scaredState = SCRD;
      break;
    }      
    servo_speed(12, 100);
    servo_speed(12, 100);
    break;
    
    
    case SK2:
      if (condition == 0){
        initial_t = time(NULL); //time when first entered SK1
        condition = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 0.5){
          //occurs if 0.5 seconds ahve passed
          condition = 0;
          scaredState = SK1;
        }          
      } 
    if (irSense == 1){
      scaredState = SCRD;
      break;
    }      
    servo_speed(12, -100);
    servo_speed(12, -100);
    break;
    
    
    case SCRD:
      if (condition == 0){
        initial_t = time(NULL); //time when first entered MAD
        condition = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 4){
          //occues if 4 seconds have passed
          condition = 0;
          scaredState = START;
        }          
      }
      servo_speed(12, 200);
      servo_speed(12, -200);
      break;
  }    
}  
