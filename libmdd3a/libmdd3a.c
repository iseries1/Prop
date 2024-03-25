/**
 * @brief Dual Channel Motor Driver
 * @author Michael Burmeister
 * @date February 19, 2023
 * @version 1.0
 * 
*/

#include "mdd3a.h"
#include "simpletools.h"

#define M2B 16
#define M2A 17
#define M1B 18
#define M1A 19


int main()
{
  mdd3a_Init(M1A, M1B, M2A, M2B);

  pause(2000);
  
  printi("Starting....\n");
  
  for (int i=1000;i<2000;i+=10)
  {
    mdd3a_SetPWM(i, i);
    pause(500);
  }

  mdd3a_Stop();
  
  printi("Done\n");
  
  while(1)
  {
    pause(1000);
    
  }  
}
