/**
 * @brief SSD1306 Display Driver
 * @author Michael Burmeister
 * @date March 14, 2018
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "SSD1306.h"

#define SDA 21
#define SCL 20
#define DC 22
#define RST 19
#define CS 18


int main()
{
  SSD1306_init(SCL, SDA, CS, DC, RST);
  pause(500);
  SSD1306_auto(1);
  SSD1306_writeStr(0, 0, "SSD1306");
  SSD1306_writeSStr(0,40, "Doug");
  print("Done");
  
  while(1)
  {
    pause(1000);
    
  }  
}
