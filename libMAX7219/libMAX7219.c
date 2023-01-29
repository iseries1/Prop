/**
 * @brief Driver for MAX7219 7 segment board
 * @author Michael Burmeister
 * @date December 2, 2021
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "MAX7219.h"

#define MAXDIN 18
#define MAXCS 17
#define MAXCLK 16

int i;


int main()
{
  
  MAX7219_init(MAXCLK, MAXDIN, MAXCS);
  
  MAX7219_test(1);
  
  pause(2000);
  
  MAX7219_test(0);
  
  MAX7219_print(12345678, 2);
    
  while(1)
  {
    pause(1000);
  }  
}
