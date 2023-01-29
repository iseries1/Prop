/**
 * @brief Honeywell Humidity and Temperature chip
 * @author Michael Burmeister
 * @date January 16, 2016
 * @version 1.1
 * 
*/

#include "simpletools.h"
#include "hih8120.h"

#define SCLK 6
#define SDA 7

  int i;
  int t;
  int h;
  int c;
  int rh;
  int rt;
  int s;

int main()
{
  i = hih8120_open(SCLK, SDA);
  
  if (i < 1)
    exit(1);
  
  while (1)
  {
    pause(10000);
  
    h = hih8120_humidity();
    t = hih8120_fahrenheit();
    c = hih8120_celsius();
    rh = hih8120_rawhumidity();
    rt = hih8120_rawtemperature();
    s = hih8120_status();
    
    print("Humidity: %d (%d), Temperature: %d (%d)(%d) status: %d\n", h, rh, t, c, rt, s);
  }
  hih8120_close();
}
