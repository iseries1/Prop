/**
 * @brief Driver for DS3231 real time clock HW-084
 * @author Michael Burmeister
 * @date Month Day, Year
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "DS3231.h"

#define DSCLK 7
#define DSSDA 6

time_t tm;


int main()
{
  int i;
  
  DS3231_Open(DSCLK, DSSDA);
  
  //DS3231_SetDate(4,19,2023);
  //DS3231_SetTime(6,04,00);
  
  DS3231_SetDateTime();
  
  
  
 
  while(1)
  {
    time(&tm);
    	i = DS3231_Temperature();
    	printi("Temp %d, Date(%d): %s", i, tm, asctime(localtime(&tm)));
     pause(1000);
    
  }  
}
