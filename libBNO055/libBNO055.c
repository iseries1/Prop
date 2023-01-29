/**
 * @brief BOSCH BNO055 driver library
 * @author Michael Burmeister
 * @date March 14, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "BNO055.h"

#define CLK 0
#define DTA 1

int i;
short heading, roll, pitch;

int main()
{
  int t;
  i = 0;
  
  i = BNO055_init(CLK, DTA);

  printi("Chip id: %x\n", i);
  
  i = BNO055_ACCID();
  printi("ACC: %x\n", i);
  
  i = BNO055_MAGID();
  printi("MAG: %x\n", i);
  
  i = BNO055_GYROID();
  printi("Gyro: %x\n", i);
  
  i = BNO055_getOperatingMode();
  printi("Mode: %d\n", i);
  
  t = BNO055_Temperature();
  print("Temp: %d\n", t);
  
  i = BNO055_OperatingMode(NDOF);
  pause(1000);
  
  while(1)
  {
    i = BNO055_getEulerAngle(&heading, &roll, &pitch);
    t = BNO055_getCalibration();
    printi("Cal: %02x heading: %d, roll: %d, pitch: %d\n", t, heading, roll, pitch);
    pause(1000);
    
  }  
}
