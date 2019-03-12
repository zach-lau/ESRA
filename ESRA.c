/*
The main architecture for the ESRA
*/

#include "simpletools.h"
#include "servo.h"

#include "angry.h"
#include "excited.h"
#include "scared.h"
#include "confused.h"

enum emotion{ANGRY, EXCITED, SCARED, CONFUSED};


emotion state = EXCITED;

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
      
    }
  }  
      
}