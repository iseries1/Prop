/**
 * @brief MS5607 pressure drive
 * @author Michael Burmeister
 * @date May 24, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "ms5607.h"

#define CLK 3
#define SDA 4

int i;

int main()
{
  ms5607_init(CLK, SDA, RSLT_256);

  i = ms5607_rawtemperature();
  print("Temp:%d\n", i);
  
  i = ms5607_rawpressure();
  print("Pressure:%d\n", i);
  
  i = ms5607_temperature();
  print("Temp: %d\n", i);
  
  i = ms5607_fahrenheit();
  print("Temp: %d\n", i);
  
  i = ms5607_pressure();
  print("Pressure: %d\n", i);
  
  i = ms5607_mercury();
  print("Mecury: %d\n", i);
  
  while(1)
  {
    pause(1000); 
  }  
}
