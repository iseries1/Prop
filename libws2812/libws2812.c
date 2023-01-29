/**
 * @brief Drive Neo Pixel ws2812 leds
 * @author Michael Burmeister
 * @date November 11, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "ws2812.h"

#define PIN 0

unsigned long Leds[12];

int main()
{
  printi("Starting\n");
  
  for (int i=0;i<12;i++)
    Leds[i] = -1;
  
  ws2812_set(PIN, Leds, 12);
  
  for (int i=0;i<12;i++)
    Leds[i] = 0;
  
  pause(5000);
  
  ws2812_set(PIN, Leds, 12);
  
  printi("Done\n");

  while(1)
  {
    pause(1000);
    
  }  
}
