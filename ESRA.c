/*
The main architecture for the ESRA
*/

#include "simpletools.h"
#include "servo.h"

#include "angry.h"
#include "excited.h"
#include "scared.h"
#include "confused.h"

int irSense;

enum emotion{ANGRY, EXCITED, SCARED, CONFUSED};

enum emotion state = ANGRY;

int main(){ 
  
  while(1){
    switch(state){
      case ANGRY:
        angry();
        break;
      case EXCITED:
        excited();
        break;
      case SCARED:
        scared();
        break;
      case CONFUSED:
        confused();
        break;
      default:
        ;
      
    }
  }  
      
}
