/**
 * @brief Driver for MAX7219 7 segment board
 * @author Michael Burmeister
 * @date December 2, 2021
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "MAX7219.h"


int _CLKPIN;
int _DTAPIN;
int _SELPIN;

void MAX7219_init(int clk, int dta, int sel)
{
  _CLKPIN = clk;
  _DTAPIN = dta;
  _SELPIN = sel;
  for (int i=1;i<9;i++)
    MAX7219_set(i, 0x0f, 0);
  MAX7219_mode(0xff); // all digits
  MAX7219_intensity(50); // brightness 50%
  MAX7219_digits(8); // all digits enabled
  MAX7219_shutdown(1); // no sleeping
}
  
void MAX7219_test(int state)
{
  int i;
  
  i = MAX7219_DISPLAYTEST | state;
  
  low(_SELPIN);
  shift_out(_DTAPIN, _CLKPIN, MSBFIRST, 16, i);
  high(_SELPIN);
}

void MAX7219_digits(int digits)
{
  
  digits = digits - 1;
  digits = digits | MAX7219_SCANLIMIT;
  low(_SELPIN);
  shift_out(_DTAPIN, _CLKPIN, MSBFIRST, 16, digits);
  high(_SELPIN);
}

void MAX7219_intensity(int percent)
{
  percent = percent / 6;
  if (percent > 0)
    percent--;
  percent = percent | MAX7219_INTENSITY;
  
  low(_SELPIN);
  shift_out(_DTAPIN, _CLKPIN, MSBFIRST, 16, percent);
  high(_SELPIN);
}

void MAX7219_set(int digit, int value, int decimal)
{
  digit = digit << 8;
  value = value | digit;
  
  if (decimal != 0)
    value = value | 0x80;

  low(_SELPIN);
  shift_out(_DTAPIN, _CLKPIN, MSBFIRST, 16, value);
  high(_SELPIN);
}

void MAX7219_mode(int mask)
{
  
  mask = mask | MAX7219_DECODE;
  
  low(_SELPIN);
  shift_out(_DTAPIN, _CLKPIN, MSBFIRST, 16, mask);
  high(_SELPIN);
}

void MAX7219_shutdown(int onoff)
{
  onoff = onoff | MAX7219_SHUTDOWN;
  
  low(_SELPIN);
  shift_out(_DTAPIN, _CLKPIN, MSBFIRST, 16, onoff);
  high(_SELPIN);
}

void MAX7219_print(long value, int decimal)
{
  int t;
  
  for (int i=1;i<9;i++)
  {
    t = value % 10;
    MAX7219_set(i, t, decimal == i);
    value = value / 10;
  }    
}
