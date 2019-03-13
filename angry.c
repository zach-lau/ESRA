#include "simpletools.h"                      
#include "servo.h"

enum AngryState{START, OB1, OB2, MAD};

enum AngryState angryState = START;

time_t initial_t;
time_t current_t;
int condition = 0;

int angry(void){
  irSense = input(7);
  switch(angryState){
    case START:
      servo_speed(12, 200);
      servo_speed(13, -200);
      pause(100);
      if (irSense == 1){
        angryState = OB1;
      }        
      break;
      
    case OB1:
      if (condition == 0){
        initial_t = time(NULL); //time when first entered OB1
        condition = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) < 0.93){
          //occues if enough time passed for the robot to turn "right"
          condition = 0;
          angryState = START;
        }          
      }        
      if (irSense == 1){
        angryState = OB2;
        break;
      } 
      
      servo_speed(12, -200);
      servo_speed(13, -200);
      pause(100);     
      break;
      
    case OB2:
      if (condition == 0){
        initial_t = time(NULL); //time when first entered OB2
        condition = 1;
      } else {
        current_t = time(NULL); // current time
        if (((double) (current_t) - (double) (initial_t)) < 0.93){
          //occues if enough time passed for the robot to turn "right"
          condition = 0;
          angryState = START;
        }          
      }        
      if (irSense == 1){
        angryState = MAD;
        break;
      } 
      
      servo_speed(12, -100);
      servo_speed(13, -100);
      pause(100); 
      break;
      
    case MAD:
      if (condition == 0){
        initial_t = time(NULL); //time when first entered MAD
        condition = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) < 5){
          //occues if 5 seconds have passed
          condition = 0;
          angryState = START;
        }          
      }        
    
      servo_speed(12, 255);
      servo_speed(13, 255);
      pause(100);

      break;
    default:
      angryState = START;
      break;
      ;
  }    
  return 0;
}

