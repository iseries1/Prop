/**
 * @brief HX8357 320x480 display panel
 * @author Michael Burmeister
 * @date March 11, 2019
 * @version 1.0
*/

#include "simpletools.h"
#include "HX8357.h"


#define LITE 9
#define RST 10
#define DC 11
#define CS 12
#define MOSI 13
#define MISO 14
#define CLK 15

int i;
unsigned long PCNT;

int main()
{
  i = HX8357_open(CLK, MISO, MOSI, CS, DC, RST, LITE);
  
  print("Power: %x\n", i);

  if ((i & 0x08) == 0)
    HX8357_sleepOn(0);

  // Is display on
  if ((i & 0x04) == 0)
    HX8357_displayOn(1);
  
  i = HX8357_control();
  print("Control: %x\n", i);

  HX8357_rotation(1);

  HX8357_cls(HX8357_BLACK);
  
  HX8357_writeSStr(10, 10, "Hello World");
  
  HX8357_writeStr(10, 100, "Hello World");
  
  HX8357_writeXStr(10, 160, "Hello World");
  
  HX8357_drawBox(50, 50, 100, 100, HX8357_color(255,0,0));
  
  HX8357_displayMode(0);
  
  print("Done\n");
  
  while(1)
  {
    pause(1000);
    
  }  
}
