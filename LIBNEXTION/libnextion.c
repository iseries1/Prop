/**
 * @brief Interface to Nextion display
 * @author Michael Burmeister
 * @date December 21, 2017
 * @version 1.0
 * 
*/
#include "fdserial.h"
#include "simpletools.h"
#include "nextion.h"

#define Rx 1
#define Tx 0


int main()
{
  int i;
  
  print("Open Port\n");
  
  i = Nextion_open(Rx, Tx, 9600);
  
  print("Nextion: %d\n", i);
  
  print("Serial Number: %s\n", Nextion_serialno());
  
 
  
  while(1)
  {
    
    
  }  
}
