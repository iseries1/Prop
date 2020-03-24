/**
 * @brief LCD Display Library
 * @date December 25, 2014
 * @author Michael Burmeister
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "LcdDisplay.h"
#include "serial.h"

serial *LcdDsp = NULL;
int DSPON = 0;

void Lcd_Open(char Tx, int Baud)
{
  LcdDsp = serial_open(Tx, Tx, 0, Baud);
}

void Lcd_PosCursor(int x, int y)
{
  int i = 128;
  
  if (y > 1)
    return;
  y = y * 20;
  i = y + x + i;
  if (LcdDsp != NULL)
    serial_txChar(LcdDsp, i);
  return;
}

void Lcd_PlayNote(int n, int len)
{
  int i = len + 208;
  int j = n + 220;
  if (LcdDsp != NULL)
  {
    serial_txChar(LcdDsp, i);
    serial_txChar(LcdDsp, j);
  }
  return;
}

void Lcd_Clr()
{
  if (LcdDsp != NULL)
    serial_txChar(LcdDsp, 12);
  Lcd_Set(1, 1, 0);
}

void Lcd_Set(int O, int C, int B)
{
  int i = 21;
  if (O)
  {
    i++;
    if (C)
      i += 2;
    if (B)
      i++;
  }
  if (LcdDsp != NULL)
    serial_txChar(LcdDsp, i);
}

void Lcd_BackLight(int O)
{
  int i = 18;
  if (O)
  {
    DSPON = 1;
    i--;
  }
  else
    DSPON = 0;
    
  if (LcdDsp != NULL)
    serial_txChar(LcdDsp, i);
}

void Lcd_Chars(char *c)
{
  int i = 0;
  if (LcdDsp == NULL)
    return;
  for (i=0;i<50;i++)
  {
    if (c[i] == 0)
      break;
    serial_txChar(LcdDsp, c[i]);
  }
}

void Lcd_Char(char c)
{
  serial_txChar(LcdDsp, c);
}
  
void Lcd_Close()
{
  if (LcdDsp != NULL)
  {
    if (DSPON == 1)
        serial_txChar(LcdDsp, 18);

    DSPON = 0;
    serial_close(LcdDsp);
  }
  LcdDsp = NULL;
}  