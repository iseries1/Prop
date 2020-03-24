/**
 * @brief Set the time values
 * @author Michael Burmeister
 * @date October 13, 2018
 * @version 1.0
 * 
*/
#include "settime.h"
#include "simpletools.h"

time_t t;

int main()
{
  
  setTime(2018, 10, 13, 6, 24, 0);
 
  while(1)
  {
    t = time(&t);
    print("%s \n", asctime(localtime(&t)));
    pause(1000);
  }  
}
