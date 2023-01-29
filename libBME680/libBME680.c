/**
 * @brief BME680 Environmental Sensor
 * @author Michael Burmeister
 * @date December 7, 2019
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "BME680.h"

#define BMESCL 8
#define BMESDA 9

int i;

int main()
{

  i = BME680_init(BMESCL, BMESDA);
  
  printi("ID: %d\n", i);

 
  while(1)
  {
    pause(1000);
    
  }  
}
