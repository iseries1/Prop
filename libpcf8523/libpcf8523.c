/**
 * @brief Real Time Clock Driver
 * @author Michael Burmeister
 * @date April 17, 2023
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "pcf8523.h"

#define PCFCLK 18
#define PCFDTA 17

time_t tm;


int main()
{
  int i;
  int h, m, s;
  int y, mn, d;
  
  i = PCF8523_Init(PCFCLK, PCFDTA);
  
  i = PCF8523_Control();
  printi("Control: %x\n", i);
  
  //PCF8523_SetTime(9,02,00);
  //PCF8523_SetDate(04,19,2023);
    
  s = PCF8523_Seconds();
  m = PCF8523_Minutes();
  h = PCF8523_Hour();
  d = PCF8523_Day();
  mn = PCF8523_Month();
  y = PCF8523_Year();
  
  printi("time: %d:%d:%d Date: %d/%d/%d\n", h, m, s, mn, d, y);
  
  PCF8523_SetDateTime();
  
  i = PCF8523_GetAlarm();
  
  printi("Alarm: %x\n", i);
  
  while(1)
  {
    time(&tm);
    printi("Date(%d): %s", tm, asctime(localtime(&tm))); 
    pause(1000);    
  }  
}

