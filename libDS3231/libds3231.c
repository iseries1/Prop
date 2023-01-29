/**
 * @brief Driver for DS3231 real time clock HW-084
 * @author Michael Burmeister
 * @date Month Day, Year
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "DS3231.h"

#define DSCLK 0
#define DSSDA 1

time_t tm;


int main()
{
  int i;
  
  DS3231_Open(DSCLK, DSSDA);
  
  
  DS3231_SetDateTime();
  
 
  while(1)
  {
    time(&tm);
    	i = DS3231_Temperature();
    	printf("Temp %d, Date: %s", i, asctime(localtime(&tm)));
     pause(1000);
    
  }  
}
