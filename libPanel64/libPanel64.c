/**
 * @brief Drive Panel 64 LED
 * @author Michael Burmeister
 * @date May 8, 2021
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "Panel64.h"

int main()
{
  int c;
  
  Panel_Start();

  c = Panel_Color(1, 1, 1);

  Panel_TextColor(c, 0);
  Panel_WriteSStr(10,10, "Hello");
  Panel_WriteSStr(10,18, "World");
  Panel_DrawLine(10, 26, 50, 26, c);
  pause(5000);
  Panel_ScrollVertical(8);
  pause(5000);
  Panel_ScrollHorizontal(8);
 
  while(1)
  {
    pause(1000);
    // Add main loop code here.
    
  }  
}
