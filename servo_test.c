/*
  Test code to help determine if robot's
  servos are properly calibrated and aligned
  with eachother. 
*/
#include "simpletools.h"                      // Include simple tools
#include "servo.h"                            // Include servo commands

int main()                                    // Main function
{
  int elapsed = 0;                            // Set initial time elapsed = 0
  while(elapsed < 60)                         // Exit loop if time elapsed
                                              // is greater than 60s
  {
     servo_speed(12,-200);                    // Set right servo speed
     servo_speed(13,200);                     // Set left servo speed
     pause(5000);                             // Wait 5s before next line
     servo_speed(12,200);                     // Reverse right servo speed
     servo_speed(13,-200);                    // Reverse left servo speed
     pause(5000);
     elapsed += 10;                           // Add 10s on to elapsed time
  }
  servo_speed(12,0);                          // Set right servo speed to 0
  servo_speed(13,0);                          // Set left servo speed to 0
  return 0;  
}
