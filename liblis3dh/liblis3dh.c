/**
 * @brief Device Driver for LIS3DH
 * @author Michael Burmeister
 * @date May 8, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "lis3dh.h"

#define LISCS 5
#define LISCK 2
#define LISDI 3
#define LISDO 4

int i;
short x, y, z;


int main()
{
  i = lis3dh_init(LISCK, LISDI, LISDO, LISCS);
  
  print("chip id: %x\n", i);
  
  lis3dh_updateRate(UP_100HZ);
  
  pause(100);
  
  lis3dh_enableADC();
  
  i = lis3dh_readADC1();
  
  print("Voltage: %d\n", i);
  
  i = lis3dh_status();
  
  lis3dh_range(SCALE_16G);
  
  print("Status: %x\n", i);
  
  while(1)
  {
    lis3dh_axis(&x, &y, &z);
    print("X: %d, Y: %d, Z: %d\n", x, y, z);
    pause(1000);
    
  }  
}
