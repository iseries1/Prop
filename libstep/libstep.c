/**
 * @brief Control Stepper motors
 * @author Michael Burmeister
 * @date November 29, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "step.h"

#define ENABLEA 8
#define STEPA 9
#define DIRECTIONA 10
#define ENABLEB 11
#define STEPB 12
#define DIRECTIONB 13


int m, n;

int main()
{
  m = Step_Start(ENABLEA, DIRECTIONA, STEPA);
  n = Step_Start(ENABLEB, DIRECTIONB, STEPB);
  
  printi("Starting %d \n", m);
  Step_Step(m, 2000);
  Step_Step(n, -5000);
  Step_Wait();
  printi("Step 1\n");
  pause(5000);
  Step_Step(m, -2000);
  Step_Step(n, 5000);
  Step_Wait();
  printi("Step 2\n");
  pause(5000);
  Step_Step(m, 0);
  Step_Step(n, 0);
  Step_Wait();
  
  printi("Done\n");
  
  while(1)
  {
    pause(1000);    
  }  
}
