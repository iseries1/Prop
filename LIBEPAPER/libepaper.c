/**
 * @brief Driver for e-Paper display
 * @author Michael Burmeister
 * @date July 7, 2019
 * @version 1.0
 * 
*/
#include "epaper.h"
#include "simpletools.h"


#define DIN 2
#define CLK 3
#define CS 4
#define DC 5
#define RST 6
#define BUSY 7

int i;

int main()
{
  i = epaper_init(DIN, CLK, CS, DC, RST, BUSY);
  
//  printi("Value: %d\n", i);
  
  epaper_cls(1);
  
  char *x = epaper_buffer();

//  epaper_drawLine(10,10,50,50,0);
//  epaper_writeStr(8, 8, "Hello World");
  epaper_writeXStr(8, 8, "Hello");
  epaper_writeXStr(64, 8, "World");
//  epaper_writeChar(8, 32, 'A');
//  epaper_drawLine(120, 32, 100, 64, 0);
  epaper_update();
  printi("Done\n");
  epaper_sleep(1);
  
  while(1)
  {
    pause(1000);    
  }  
}
