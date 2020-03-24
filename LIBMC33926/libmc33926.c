/**
 * @brief Driver logic for MC33926 motor drive
 * @author Michael Burmeister
 * @date June 28, 2019
 * @version 1.0
 * 
*/
#include "mc33926.h"
#include "simpletools.h"

void sidetest(void);


#define LIN1 14
#define LIN2 15
#define RIN1 11
#define RIN2 12
#define LPWM 13
#define RPWM 10

int main()
{
  
//  sidetest();
//  while (1);
  
  mc33926_init(LIN1, LIN2, LPWM, RIN1, RIN2, RPWM);
  
  for (int i=1000;i<2000;i+=10)
  {
    mc33926_setPWM(i, i);
    pause(250);
  }
  
  while(1)
  {
    pause(1000);
    
  }  
}

/*
 * generate pulse every 2 milliseconds
 * 80 mhz / 80000 = 1 millisecond
 * 160000 = 2 milliseconds cut off
 */
void sidetest()
{
  unsigned long T;
  
  low(0);
  FRQA = 1;
  CTRA = 0x10000000 | 0;

  while (1)
  {
    T = CNT;
    PHSA = ~80000;

    while ((CNT - T) < 160000);
    PHSA = 0;
  }
  
}
