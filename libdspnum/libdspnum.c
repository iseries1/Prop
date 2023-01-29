/**
 * @file LibDspNum.c
 * @author Michael Burmeister
 * @date January 17, 2015
 * @version 1.0
 */

#include "simpletools.h"
#include "DspNum.h"

#define D1 16
#define D2 17
#define SA 8
#define SB 9
#define SC 10
#define SD 11
#define SE 12
#define SF 13
#define SG 14
#define DP 15

char Digits[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
int i;


int main()
{
  
  for (i=0;i<10;i++)
  {
    if ((Digits[i] & 0x01) != 0) low(SA);
    if ((Digits[i] & 0x02) != 0) low(SB);
    if ((Digits[i] & 0x04) != 0) low(SC);
    if ((Digits[i] & 0x08) != 0) low(SD);
    if ((Digits[i] & 0x10) != 0) low(SE);
    if ((Digits[i] & 0x20) != 0) low(SF);
    if ((Digits[i] & 0x40) != 0) low(SG);
    if ((Digits[i] & 0x80) != 0) low(DP);
    high(D1);
    pause(1000);
    low(D1);
    high(SA);
    high(SB);
    high(SC);
    high(SD);
    high(SE);
    high(SF);
    high(SG);
    high(DP);
  }

  while (1)
  {
    pause(1000);
  }      
}
