#include "simpletools.h"                      
#include "servo.h"

enum AngryState{START, OB1, OB2, MAD};

enum AngryState angryState = START;

int irSense;

time_t initial_t;
time_t current_t;
int condition = 0;

int angry(void){
  freqout(6, 1, 38000);
  freqout(8, 1, 38000);
  irSense = input(7);
  high(0);
  switch(angryState){
    case START:
    low(10);
      servo_speed(12, 200);
      servo_speed(13, -200);
      pause(100); 
      if (irSense != 1){
        high(27);
        pause(500);
        low(27);
        angryState = OB1;
      }
                
      break;
      
    case OB1:
      if (condition == 0){
        servo_speed(12, -200);
        servo_speed(13, -200);
        pause(1500); 
        irSense = 1;
      }else{
        pause(100);
      }        
      if (condition == 0){
        initial_t = time(NULL); //time when first entered OB1
        condition = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 8){
          //occues if enough time passed for the robot to turn "right"
          condition = 0;
          angryState = START;
        }          
      }   
      servo_speed(12, -200);
      servo_speed(13, -200);
     
       if (irSense != 1){
        high(27);
        pause(500);
        low(27);
        angryState = OB2;
        
        break;
      }     
      break;
      
    case OB2:
    high(26);
      if (condition == 0){
        initial_t = time(NULL); //time when first entered OB1
        condition = 1;
      } else {
        current_t = time(NULL); //current time
        if (((double) (current_t) - (double) (initial_t)) > 8){
          //occues if enough time passed for the robot to turn "right"
          condition = 0;
          angryState = START;
        }          
      }   
      
      
      servo_speed(12, -50);
      servo_speed(13, -50);
      pause(100); 
      if (irSense != 1){
        high(27);
        pause(500);
        low(27);
        angryState = MAD;
        break;
      } 
      break;
      
    case MAD:
      
      if (condition == 0){
        initial_t = time(NULL); //time when first entered MAD
        condition = 1;
      } else {
        current_t = time(NULL);
        if (((double) (current_t) - (double) (initial_t)) > 10){
          //occues if 5 seconds have passed
          condition = 0;
          angryState = START;
        }          
      }        
      
      servo_speed(12, 255);
      servo_speed(13, 255);
      low(0);
      low(10);
      pause(500);
      high(10);
      pause(500);
      //pause(100);

      break;
    default:
      angryState = START;
      break;
      ;
  }    
  return 0;
}
