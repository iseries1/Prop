/**
 * @brief Test program for ICM20948 9Dof sensor
 * @author Michael Burmeister
 * @date February 20, 2023
 * @version 1.0
 * 
*/

#include "icm20948.h"
#include "simpletools.h"

#define ICMCLK 8
#define ICMDTA 9


int i;


int main()
{
  short gx, gy, gz;
  short ax, ay, az;
  short mx, my, mz;
  
  i = ICM20948_Init(ICMCLK, ICMDTA);
  if (i != 0)
  {
    printi("ICM-20948 not found!\n");
    while (1)
      pause(5000);
  }

  i = ICM20948_Temp();
  printi("Temp:%d\n", i);

  ICM20948_ByPass(1); // Set bypass to read Mag Registers

  i = ICM20948_MagCtrl();
  printi("Mag: %x\n", i);
    
  ICM20948_MagMode(8);

  i = ICM20948_MagCtrl();
  printi("Mag: %x\n", i);


  while(1)
  {
    i = ICM20948_Mag(&mx, &my, &mz);
    ICM20948_Accel(&ax, &ay, &az);
    ICM20948_Gyro(&gx, &gy, &gz);
    printi("Mag(%x): %d, %d, %d ", i, mx, my, mz);
    printi("Accel: %d, %d %d ", ax, ay, az);
    printi("Gyro: %d, %d, %d\n", gx, gy, gz);
    
    high(26);
    pause(500);
    low(26);
    pause(500);
  }  
}
