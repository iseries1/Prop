/**
 * @brief Interface to Nextion display
 * @author Michael Burmeister
 * @date December 21, 2017
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "nextion.h"

#define Rx 15
#define Tx 14
unsigned char *Buf;

short X, Y;


int main()
{
  int i;
  
  print("Open Port\n");
  
  i = Nextion_open(Rx, Tx, 9600);
//  Nextion_setbaud(115200);
//  i = Nextion_open(Rx, Tx, 115200);
  
  print("Nextion: %d\n", i);
  
  printi("Serial Number: %s\n", Nextion_serialno());
  
  printi("Event: %d\n", Nextion_event());
  
  Nextion_cls(0);
  
  i = Nextion_color(0, 63, 0);

  Nextion_fill(20, 50, 20, 20, i);
  
  Nextion_line(20, 100, 100, 100, i);
  
  Nextion_circle(20, 200, 10, i);
  
  Nextion_fillcircle(100, 200, 10, i);
  
  Nextion_xstr(20, 150, 100, 30, 1, i, 0, 0, 0, 3, "Test Data");
  
  print("Color: %d\n", i);
  
  Nextion_touch(1);
  
  pause(1000);
  
  Nextion_debug();
  
  while(1)
  {
    pause(500);
    i = Nextion_event();
    if (i != 0)
    {
      printi("Event: %d\n", i);
      if (i == 23)
      {
        i = Nextion_touchxy(&X, &Y);
        if (i == 0)
          printi("X: %d, Y: %d\n", X, Y);
      }
    }              
  }  
}
