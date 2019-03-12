#include "servo.h"

enum angryState{START, OB1, OB2, MAD};

int angry(void){
  servo_speed(12, 200);
  servo_speed(13, -200);
  pause(100);
  return 0;
}