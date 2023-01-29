/**
 * @file windspd.c
 * @brief Determine the wind speed 
 * @author Michael Burmeister
 * @date January 27, 2016
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "windspd.h"

void windspdn(void *par);
void windcount(void *par);
static int millis(void);

int wHall;
int volatile WndSpd;
int volatile AWnd[60];
int volatile _Count;
int wCog;
int wCog2;
unsigned long _PCNT;


// Start Wind Speed Monitor
int windspd_open(int hall)
{
  int *i;
  
  WndSpd = -1;
  wHall = hall;
  
  cog_run(&windcount, 50);
  i = cog_run(&windspdn, 50);
  return cog_num(i);
}

/*
 * Count each transition from low to high
 *
 */
void windspdn(void *par)
{
  input(wHall);
  int Mask = 1 << wHall;
  _Count = 0;
  while (1)
  {
    waitpeq(Mask, Mask); //wait on low state
    waitpeq(0, Mask); //wait on high state
    _Count++;
  }
}

/*
 * count the number of pulse per minute
 *
*/
void windcount(void *par)
{
  int i, t;

  wCog2 = -1;
  millis();
  t = 0;
  i = 0;
  while (wCog2)
  {
    t += millis();
    if (t > 60000)  // once ever minute
    {
      AWnd[i] = _Count;
      _Count = 0;
      if (++i >= 60)
        i = 0;
      t -= 60000;
    }      
  }
  cogstop(cogid());
}
  
// Get current wind speed mph in 10ths
int windspd_speed(void)
{
  int i;
  int t;
  
  // cup len is 3.5"
  // circumference is D*PI (7 * 3.1415926) 22 in/rev
  // 12 inches in one foot 1.83 ft/rev
  // 5280 feet in mile .0002975 miles/rev
  // or 2880 rev = 1 mile or 2880 rev in an hour = 1 mph
  // 2880/60 = 48 rev/min = 1 mph
//  i = (WndSpd * 10 / 4) / 48;
  
  t = 0;
  for (i=0;i<60;i++)   // one hour of data per minute
    t += AWnd[i];
    
         
  i = t / 288;  // average wind speed in tenths of mile
  
  return i;
}

void windspd_close(void)
{
  wCog = 0;
  wCog2 = 0;
}  

// keep accurate time
static int millis(void)
{
  long t;
  
  t = CNT + 280 - _PCNT;
  _PCNT = CNT;
  if (t < 0)
    t = UINT32_MAX + t;

  _PCNT = _PCNT - t % ms;
  t = t/ms;
  return t;
}
