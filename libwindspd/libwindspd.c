/**
 * @brief Determine the wind speed 
 * @author Michael Burmeister
 * @date January 27, 2016
 * @version 1.2
 * 
*/
#include "simpletools.h"
#include "windspd.h"

#define WHALL 2


int main()
{
  int i;
  
  i = windspd_open(WHALL);
  
  while(1)
  {
    i = windspd_speed();
    print("Wind Speed: %d\n", i);
    pause(15000);
  }
  
  windspd_close();
}
