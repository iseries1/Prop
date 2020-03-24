/**
 * @brief Read Barometric Pressure Sensor
 * @author Michael Burmeister
 * @date January 25, 2016
 * @version 1.1
 * 
*/

#include "simpletools.h"
#include "ms5607.h"
void ms5607_set(void);

#define SCL 8
#define SDA 9


int main()
{
  int i;
  
  i = ms5607_open(SCL, SDA);

  pause(2000);
  // Temp: 10.7 (51), 95704 (2823)
  //ms5607_set(); 
  
  while(1)
  {
    i = ms5607_rawpressure();
    print("RawP: %d,", i);
    i = ms5607_rawtemp();
    print("RawT: %d,\n", i);
    i = ms5607_celsius();
    print("Celsius: %d, ", i);
    i = ms5607_fahrenheit();
    print("Fahrenheit: %d, ", i);
    i = ms5607_pressure();
    print("Pressure: %d, ", i);
    i = ms5607_mercury();
    print("Inches of Mercury: %d\n", i);
    pause(1000);
  }  
}
