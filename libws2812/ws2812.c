/**
 * @brief Drive Neo Pixel ws2812 leds
 * @author Michael Burmeister
 * @date November 11, 2020
 * @version 1.0
 * 
*/

#include "ws2812.h"
#include "simpletools.h"

void ws2812_set(int pin, unsigned long *leds, int num)
{
  int txmask = 1 << pin;
  unsigned long color;
  unsigned int w;
  int bits;
  unsigned long hi, lo;
  
  hi = 72;
  lo = 28;
  
  low(pin);
  
  for (int j=0;j<num;j++)
  {
    color = leds[j];
    color = color << 8;
  
    for (int i=0;i<24;i++)
    {
      __asm__ volatile (
        "          rcl     %[color], #1 wc  \n\t"
        "    if_c  mov     %[w], %[hi]      \n\t"
        "    if_nc mov     %[w], %[lo]      \n\t"
        "          or      outa, %[txmask]  \n\t"
        "          add     %[w], cnt        \n\t"
        "    if_c  waitcnt %[w], %[lo]      \n\t"
        "    if_nc waitcnt %[w], %[hi]      \n\t"
        "          andn    outa, %[txmask]  \n\t"
        "          waitcnt %[w], #0         \n\t"
                   : [w]      "+r" (w),
                     [color]  "+r" (color)
                   : [txmask] "r"  (txmask),
                     [hi]     "r"  (hi),
                     [lo]     "r"  (lo)
         );
    }
  }
}  