/**
 * @brief WIO E5 Driver
 * @author Michael Burmeister
 * @date February 14, 2023
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "wioe5.h"

#define WRX 0
#define WTX 1

char Buffer[256];
char *d;

int main()
{
  int i;
  
  printi("Starting\n");
  
  i = WIOE5_Init(WRX, WTX);
  if (i != 4011)
  {
    printi("Startup Error\n");
    while (1)
      pause(500);
  }

  WIOE5_SetMode(1);
  
  i = WIOE5_Join();
  if (i < 1)
  {
    printi("Join Failed\n");
    while (1)
      pause(1000);
  }
  
  i = WIOE5_SendHex(NULL);
  printi("Hex: %d\n", i);
  
  d = WIOE5_GetData();
  if (i > 2)
    memcpy(&i, &d[16], 4);

  printi("Data: %d\n", d);
  
  printi("Done\n");  
 
  while(1)
  {
    pause(500);
    
  }  
}
