/**
 * @brief Control Stepper motors
 * @author Michael Burmeister
 * @date November 29, 2020
 * @version 1.0
 * 
*/

#include "step.h"
#include "simpletools.h"

void doSteps(void *);



int volatile Stepper[5];
int volatile Busy;
int volatile Total = 0;
int Enable, Direction, Step;

int Step_Start(int enable, int direction, int step)
{
  Enable = enable;
  Direction = direction;
  Step = step;
  Stepper[Total] = 0;
  cog_run(&doSteps, 60);
  pause(1000);
  return Total++;
}

void Step_Step(int motor, int steps)
{
  if (motor < 5)
    Stepper[motor] = steps;
}

void Step_Wait(void)
{
  while (Busy)
    usleep(100);
}

void Step_Disable(void)
{
  
}
  
void doSteps(void *par)
{
  int enable;
  int direction;
  int step;
  int current;
  int driver;
  int i, s, c, t;
  int rampup, rampdown;
  
  enable = Enable;
  direction = Direction;
  step = Step;
  driver = Total;
  low(enable);
  low(step);
  low(direction);
  current = 0;
  Stepper[driver] = 0;
  
  while (1)
  {
    i = Stepper[driver];
    if (current != i)
    {
      s = 900;
      Busy |= (1 << driver);
      if (current > i)
      {
        high(direction);
        c = -1;
      }
      else
      {
        low(direction);
        c = 1;
      }
      t = abs(current - i) - 1600;
      if (t < 0)
      {
        rampup = 800 + t/2;
        rampdown = rampup;
        if (t & 1)
          rampup++;
      }
      else
      {
        rampup = 800;
        rampdown = rampup;
      }
      for (i=0;i<rampup;i++)
      {
        high(step);
        usleep(s--);
        low(step);
        current += c;
      }
      for (i=0;i<t;i++)
      {
        high(step);
        usleep(s);
        low(step);
        current += c;
      }
      for (i=0;i<rampdown;i++)
      {
        high(step);
        usleep(s++);
        low(step);
        current += c;
      }
      Busy &= ~(1 << driver);
    }
    usleep(100);      
  }
}
  