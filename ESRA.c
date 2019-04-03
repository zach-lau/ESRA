/*
The main architecture for the ESRA
*/

#include "simpletools.h"
#include "servo.h"
#include "adcDCpropab.h"

int button;

enum emotion{ANGRY, HAPPY, SCARED, CONFUSED, LETHARGIC, LOVING, SAD};


enum emotion state = HAPPY;

int main(){ 
  
  while(1){
    switch(state){
      case ANGRY:
        angry();
        break;
      case HAPPY:
        happy();
        break;
      case SCARED:
        scared();
        break;
      case CONFUSED:
        confused();
        break;
      case LETHARGIC:
        lethargic();
        break;
      case LOVING:
        loving();
        break;
      case SAD:
        sad();
        break;
      default:
        ;
      
    }
    button = input (5);
    if (button){
      switch(state){
        case ANGRY:
          state = HAPPY;
          break;
        case HAPPY:
          state = SCARED;
          break;
        case SCARED:
          state = CONFUSED;
          break;
        case CONFUSED:
          state = LETHARGIC;
          break;
        case LETHARGIC:
          state = LOVING;
          break;
        case LOVING:
          state = SAD;
          break;
        case SAD:
          state = ANGRY;
          break;
      }        
    }      
  }  
}
