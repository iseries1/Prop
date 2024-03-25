/**
 * @brief Driver for TSL2591 Light Sensor
 * @author Michael Burmeister
 * @date April 15, 2023
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "tsl2591.h"


#define TSLCLK 7
#define TSLDTA 6



int main()
{
  int i, j;
  
  i = TSL2591_Init(TSLCLK, TSLDTA);
  if (i != 0)
  {
    printi("Not Found\n");
    while (1)
      pause(1000);
  }

  i = TSL2591_GetStatus();
  
  printi("Status: %x\n", i);

  
  while(1)
  {
    TSL2591_Read(&i, &j);
  
    printi("Values: %d, %d\n", i);
    pause(1000);
  }  
}
