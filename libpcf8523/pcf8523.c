/**
 * @brief Real Time Clock Driver
 * @author Michael Burmeister
 * @date April 17, 2023
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "pcf8523.h"
#include "pcf8523_reg.h"
#include <sys/time.h>

int PCF8523_BCD(int);
int PCF8523_DECIMAL(int);

short _MM[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
i2c *pcf;


int PCF8523_Init(int clk, int dta)
{
  int i;
  
  pcf = i2c_newbus(clk, dta, 1);
  
  return 0;
}

int PCF8523_Seconds(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 1);
  
  return PCF8523_BCD(data);
}

int PCF8523_Minutes(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_MINUTES, 1, &data, 1);
  
  return PCF8523_BCD(data);
}

int PCF8523_Hour(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_HOUR, 1, &data, 1);
  
  return PCF8523_BCD(data);
}

int PCF8523_DayofWeek(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_WEEKDAY, 1, &data, 1);
}

int PCF8523_Day(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_DAY, 1, &data, 1);
  
  return PCF8523_BCD(data);
}

int PCF8523_Month(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_MONTH, 1, &data, 1);
  
  return PCF8523_BCD(data);
}

int PCF8523_Year(void)
{
  int i;
  unsigned char data;
  
  i2c_in(pcf, PCF8523_ADDR, PCF8523_YEAR, 1, &data, 1);
  
  return PCF8523_BCD(data);
}

void PCF8523_SetDate(int month, int day, int year)
{
  int i;
  unsigned char data;
  
  data = PCF8523_DECIMAL(day);
  i2c_out(pcf, PCF8523_ADDR, PCF8523_DAY, 1, &data, 1);
  data = PCF8523_DECIMAL(month);
  i2c_out(pcf, PCF8523_ADDR, PCF8523_MONTH, 1, &data, 1);
  data = PCF8523_DECIMAL(year-2000);
  i2c_out(pcf, PCF8523_ADDR, PCF8523_YEAR, 1, &data, 1);
}

void PCF8523_SetTime(int hour, int minute, int second)
{
  int i;
  unsigned char data;
  
  data = PCF8523_DECIMAL(second);
  i2c_out(pcf, PCF8523_ADDR, PCF8523_SECONDS, 1, &data, 1);
  data = PCF8523_DECIMAL(minute);
  i2c_out(pcf, PCF8523_ADDR, PCF8523_MINUTES, 1, &data, 1);
  data = PCF8523_DECIMAL(hour);
  i2c_out(pcf, PCF8523_ADDR, PCF8523_HOUR, 1, &data, 1);
}

int PCF8523_SetDateTime(void)
{
  int i;
  struct timeval tv;
  
  i = ((30 + PCF8523_Year()) * 36525 + 25)/100;
  i = i + _MM[PCF8523_Month() - 1] + PCF8523_Day() - 1;
  if ((PCF8523_Year() % 4) == 0)
    if (PCF8523_Month() > 2)
      i++;
  i = i * 24 + PCF8523_Hour();
  i = i * 60 + PCF8523_Minutes();
  i = i * 60 + PCF8523_Seconds();
  
  tv.tv_usec = 0;
  tv.tv_sec = i;
  settimeofday(&tv, 0);
  return i;
}

int PCF8523_Control(void)
{
  int i;
  unsigned char data[3];
  
  i = i2c_in(pcf, PCF8523_ADDR, PCF8523_CNTRL1, 1, data, 3);
  
  i = data[0] | (data[1] << 8) | (data[2] << 16);
  
  return i;
}

void PCF8523_SetControl(int control)
{
  int i;
  unsigned char data[3];
  
  data[0] = control;
  data[1] = control >> 8;
  data[2] = control >> 16;
  
  i = i2c_out(pcf, PCF8523_ADDR, PCF8523_CNTRL1, 1, data, 3);
}

void PCF8523_SetAlarm(int minutes, int hour, int day, int dayofweek)
{
  int i;
  unsigned char data[4];
  
  if (minutes >= 0)
    data[0] = PCF8523_DECIMAL(minutes);
  else
    data[0] = 0x80;
  
  if (hour >= 0)
    data[1] = PCF8523_DECIMAL(hour);
  else
    data[1] = 0x80;
  
  if (day >= 0)
    data[2] = PCF8523_DECIMAL(day);
  else
    data[2] = 0x80;
  
  if (dayofweek >= 0)
    data[3] = PCF8523_DECIMAL(dayofweek);
  else
    data[3] = 0x80;
  
  i = i2c_out(pcf, PCF8523_ADDR, PCF8523_AMINUTES, 1, data, 4);
}

int PCF8523_GetAlarm(void)
{
  int i;
  unsigned char data[4];
  
  i = i2c_in(pcf, PCF8523_ADDR, PCF8523_AMINUTES, 1, data, 4);
  
  if ((data[0] & 0x80) == 0)
    i = PCF8523_BCD(data[0]);
  else
    i = 0x80 | PCF8523_BCD(data[0]);
  
  if ((data[1] & 0x80) == 0)
    i = i | (PCF8523_BCD(data[1]) << 8);
  else
    i = i | (0x8000 | PCF8523_BCD(data[1]) << 8);
  
  if ((data[2] & 0x80) == 0)
    i = i | (PCF8523_BCD(data[2]) << 16);
  else
    i = i | (0x800000 | PCF8523_BCD(data[2]) << 16);
  
  if ((data[3] & 0x80) == 0)
    i = i | (PCF8523_BCD(data[3]) << 24);
  else
    i = i | (0x80000000 | PCF8523_BCD(data[3] & 0xef) << 24);

  return i;
}

void PCF8523_SetOffset(int offset)
{
  int i;
  unsigned char data[0];
  
  data[0] = offset;
  i = i2c_out(pcf, PCF8523_ADDR, PCF8523_AMINUTES, 1, data, 1);
}



/* built in functions */

int PCF8523_BCD(int b)
{
  int i, j;
  
  i = b & 0x7f;
  j = i >> 4;
  i = j * 10 + (i & 0x0f);
  return i;
}

int PCF8523_DECIMAL(int d)
{
  int i, j;
  
  j = d % 10;
  i = d / 10;
  i = i << 4 | j;
  return i;
}
    