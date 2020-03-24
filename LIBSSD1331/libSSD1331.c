/**
 * @brief Colored SSD1331 Display Driver
 * @author Michael Burmeister
 * @date December 11, 2018
 * @version 1.0
 * 
*/
#include "SSD1331.h"
#include "simpletools.h"

#define OLEDDIN 7
#define OLEDCLK 6
#define OLEDCS  5
#define OLEDDC  4
#define OLEDRST 3


int main()
{
  SSD1331_init(OLEDDIN, OLEDCLK, OLEDCS, OLEDDC, OLEDRST);

  SSD1331_textColor(SSD1331_color(255, 255, 255), 0);
  
  SSD1331_writeSStr(15, 20, "Hello");

  SSD1331_drawLine(15, 50, 90, 50, SSD1331_color(255, 0, 0));
  
  SSD1331_drawBox(10, 15, 95, 55, SSD1331_color(0, 255, 0));
  
//  pause(5000);
  
//  SSD1331_scrollRight(1, 0, 63, 1);
  
//  pause(5000);
 
//  SSD1331_scrollStop();
  
  while(1)
  {
    high(26);
    sleep(1);
    low(26);
    sleep(1);
  }  
}
