#include "simpletools.h"
#include "servo.h"
#include "adcDCpropab.h"
#include "mx2125.h" 

#define BUZZER 5
#define LED 6

enum ConfusedState{START, SHAKEN, CONFUSED1, CONFUSED2, RECOVERING};

enum ConfusedState confusedState = START;

int x;
int y;
int i;

time_t timer_t;
time_t initial_t;
time_t current_t;
float vol;
int timer_c2 = 0;
int condition_c = 0;
int condition_c2 = 0;

int confused(){
	x=mx_accel(3);
	y=mx_accel(4);
	switch(confusedState){
	
		case START:
		low(BUZZER);
		low(LED);
		servo_speed(12, 0);
		servo_speed(13, 0);
		pause(1000);
		if((x>200)||(x<-200)){
		  confusedState=SHAKEN;
		} else{
			confusedState=CONFUSED1;
		}
		
		case SHAKEN:
			if((x>200)||(x<-200)){
				high(BUZZER);
				low(LED);
				pause(1000);
			}else{
				confusedState=CONFUSED1;
			}
		
		case CONFUSED1:
			if((x<100)||(x>-100)){
  			 current_t = time(NULL);
  			 for(i=0;i<2;i++){
  			 		servo_speed(12, 0);
  			 		servo_speed(13, 30);
  					i++;
  					pause(1000);
          if(i=2){
           confusedState=CONFUSED2;
          }          			
  			  if (((double)(current_t) - (double)(timer_t)) > 8){
  			     confusedState=RECOVERING;
        }          
  			 }

  			}else{
  			   confusedState=SHAKEN;
         }      
		
		
		case CONFUSED2:
			if((x<100)||(x>-100)){
				for(i=0;i<2;i++){
					servo_speed(12, 30);
					servo_speed(13, 0);
					i++;
					pause(1000);
				if(i>2){
					confusedState=CONFUSED1;
				}
         }     
        }else{
				  confusedState=SHAKEN;
        }			 		     	
		case RECOVERING: 
			if((x<100)||(x>-100)){
				current_t = time(NULL);
				servo_speed(12, 0);
				servo_speed(13, 0);
				high(LED);
				if (((double)(current_t) - (double)(timer_t)) > 5){
					confusedState=START;
				} else{
			     confusedState=SHAKEN;
			  }
       }       			
     }  
  }
