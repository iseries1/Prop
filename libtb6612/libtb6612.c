/**
 * @brief Motor Driver for Adafruit TB6612
 * @author Michael Burmeister
 * @date May 3, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "tb6612.h"


#define PWMB 2
#define BIN2 3
#define BIN1 4
#define AIN1 5
#define AIN2 6
#define PWMA 7

int i;


int main()
{
  tb6612_init(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB);
  
  for (i=1000;i<2000;i+=10)
  {
    tb6612_setPWM(i, i);
    pause(250);
  }    
 
  while(1)
  {
    pause(1000);
    
  }  
}
