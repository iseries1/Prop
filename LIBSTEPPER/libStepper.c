/**
 * @brief Stepper Motor Driver logic
 * @author Michael Burmeister
 * @date March 14, 2019
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "Stepper.h"

void doSpeed(void);
void doSingle(void);

#define ENABLEA 8
#define DIRECTIONA 10
#define STEPA 9
#define ENABLEB 11
#define DIRECTIONB 13
#define STEPB 12

int i;

int main()
{
  pause(5000);
  print("Init\n");
  Stepper_init(ENABLEA, DIRECTIONA, STEPA, ENABLEB, DIRECTIONB, STEPB);

  Stepper_enable(1);
 
  Stepper_direction(1,2);
  

  doSingle();
  
  printi("Done\n");
  
//  doSpeed();

  Stepper_speed(0,0);
  Stepper_enable(0);
  
  printi("Done\n");
  
  while(1)
  {
    pause(5000);
    
  }  
}

void doSpeed()
{
  printi("Speed\n");

  for (i=0;i<256;i++)
  {
    Stepper_speed(i, i);
    print("Speed: %d\n", i);
    pause(500);
  }
}  

void doSingle()
{
  for (i=0;i<3200;i++)
  {
    printi(".");
    Stepper_single(1,1);
    pause(1);
  }
}
  