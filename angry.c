#include "simpletools.h"                      
#include "servo.h"

//enumerator to go between the 4 states
enum AngryState{START, OB1, OB2, MAD}; 

//initializing the enumerator to the initial state
enum AngryState angryState = START;

//initializing the irSense
int irSense;

//Initializing the time variables to 
//determine how much time as passed
time_t initial_t;
time_t current_t;

//condition to help complete actions when 
//entering a state for the first time
int condition = 0;

int angry(void){
  freqout(14, 1, 38000); //sending out a signal for the ultrasonic sensors
  irSense = input(11); //checking to see if the signal was recieved back
  
  switch(angryState){
    case START:
    LED(0);              // turning the LED red
      servo_speed(12, 100); //robot moves forward
      servo_speed(13, -100);
      if (irSense != 1){   //if robot detects movement 
        angryState = OB1;  //the robot moves to the next state
      }
      break;
      
    case OB1:
      if (condition == 0){ //if this is the first time entering the state
        initial_t = time(NULL); //time when first entered OB1
        condition = 1; //sets the condition to not enter if statement again
      } else {
        current_t = time(NULL); //current time entering else statement
        if (((double) (current_t) - (double) (initial_t)) > 10){
          //occurs if the robot has remained in this state for 10 seconds
          condition = 0;       //resets condition
          angryState = START;  //robot has "calmed down"
        }          
      }   
      servo_speed(12, 50);     //robot begins to turn right
      servo_speed(13, -200);   
     pause(500);
       if (irSense != 1){      //checks to see if the robot is blocked
        angryState = OB2;      //if blocked, goes to next state
      }     
      break;
      
    case OB2:
      if (condition == 0){   //if this is the first time entering the state
        initial_t = time(NULL); //time when first entered OB1
        condition = 1;  //sets the condition to not enter if statement again
      } else {
        current_t = time(NULL); //current time entering else statement
        if (((double) (current_t) - (double) (initial_t)) > 10){
          //occurs if the robot has remained in this state for 10 seconds
          condition = 0;       //resets condition
          angryState = START;  //robot has "calmed down"
        }          
      }   
      
      servo_speed(12, 150);  //robot turns left
      servo_speed(13, 0);
      if (irSense != 1){     // if the robot is blocked again
        pause(500);
        angryState = MAD;
        break;
      } 
      break;
      
    case MAD:
      if (condition == 0){  //if this is the first time entering the state
        initial_t = time(NULL); //time when first entered MAD
        condition = 1; //sets the condition to not enter if statement again
      } else {
        current_t = time(NULL); //occurs if the robot has remained in this state for 10 seconds
        if (((double) (current_t) - (double) (initial_t)) > 10){
          //occues if 5 seconds have passed
          condition = 0;        //resets condition
          angryState = START;   //robot has "calmed down"
        }          
      }        
      
      servo_speed(12, 255);  //travles in a circle quickly
      servo_speed(13, 50);
      LED(7);                //LED blinks on and off
      pause(500);
      LED(0);
      break;
      
    default:                //as a precaution, default goes to the begining
      angryState = START;
      break;
  }    
  return 0;
}
