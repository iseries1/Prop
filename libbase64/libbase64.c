/**
 * @brief Base 64 encoder/decoder library
 * @author Michael Burmeister
 * @date March 13, 2021
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "base64.h"

char Buffer[128];


int main()
{
  int i;
  
  memset(Buffer, 0, sizeof(Buffer));
  
  i = 4260;
  
  
  Base64_Encode(&i, Buffer, 4);
  
  print(Buffer);
  print("\n");
  
  while(1)
  {
    pause(1000);    
  }  
}
