/**
 * @brief SBus receiver decoder
 * @author Michael Burmeister
 * @date December 13, 2017
 * @version 1.1
 * 
*/
#include "SBus.h"
#include "simpletools.h"

#define PIN 1


int main()
{
  int i, j, k;
  int p;
  int Max[17], Min[17];
  int W;
  
  SBus_open(PIN);
  
  pause(1000);
  
  for (i=0;i<17;i++)
  {
    Max[i] = 1000;
    Min[i] = 1000;
  }
      
  printi("Calibrate Radio by moving levers to max and min\n");
  pause(1000);
  printi("Begin you have 10 seconds\n");
  W = 0;
  while (W < 10000)
  {
    for (i=1;i<17;i++)
    {
      p = SBus_getChannel(i);
      if (p < Min[i])
        Min[i] = p;
      if (p > Max[i])
        Max[i] = p;
    }
    pause(1);
    W++;
  }    
  
  for (i=1;i<17;i++)
  {
    if (Min[i] != Max[i])
    {
      SBus_setScaledChannel(i, Min[i], Max[i]);
      printi("Channel: %d, Min: %d, Max %d\n", i, Min[i], Max[i]);
    }
  }
  
  while(1)
  {
    //i = SBus_getScaledChannel(3);
    i = SBus_getChannel(1);
    j = SBus_getChannel(2);
    k = SBus_getChannel(3);
    if (i != p)
    {
      print("%2.2x %2.2x %2.2x \n", i, j, k);
      p = i;
    }
      
//    for (i=1;i<17;i++)
//      print("%d, ", SBus_getAdjChannel(i));
//    print("\n");
//    pause(250);
  }  
}
