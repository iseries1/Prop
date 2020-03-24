/**
 * @brief Set the time values
 * @author Michael Burmeister
 * @date October 13, 2018
 * @version 1.0
 * 
*/

#include "time.h"
#include "sys/time.h"

short _MM[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

void setTime(short y, short m, short d, short h, short mi, short s)
{
  struct timeval tv;
  
  int v = (y-1970)*36525/100;
  
  v = v + _MM[m-1] + d - 1; //days
  v = v * 24 + h; //hours
  v = v * 60 + mi; //minutes
  v = v * 60 + s; //seconds
  tv.tv_usec = 0;
  tv.tv_sec = v;
  settimeofday(&tv, 0);
}
  