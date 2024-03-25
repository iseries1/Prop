/**
 * @brief Driver for TSL2591 Light Sensor
 * @author Michael Burmeister
 * @date April 15, 2023
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "tsl2591_reg.h"
#include "tsl2591.h"

i2c *tsl;


int TSL2591_Init(int clk, int dta)
{
  int i;
  
  tsl = i2c_newbus(clk, dta, 0);
  
  i = TSL2591_GetID();
  if (i != 0x50)
    return -1;

  TSL2591_Enable(1);

  pause(500);
    
  TSL2591_Read(&i, &i);
  
  return 0;
}

int TSL2591_GetID(void)
{
  int i;
  unsigned char b;
  
  b = 0;
  
  i = i2c_in(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_ID, 1, &b, 1);
  
  i = b;
  return i;
}

int TSL2591_GetStatus(void)
{
  int i;
  unsigned char b;
  
  i = i2c_in(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_STATUS, 1, &b, 1);
  
  i = b;
  return i;
}

int TSL2591_Read(int *ch0, int *ch1)
{
  int i;
  short v, v1;

  v = 0;
  v1 = 0;
  i = i2c_in(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CHAN0, 1, (unsigned char*)&v, 2);
  i = i2c_in(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CHAN1, 1, (unsigned char*)&v1, 2);
  
  *ch0 = v;
  *ch1 = v1;
}

void TSL2591_Reset(void)
{
  int i;
  unsigned char b = 0x80;
  
  i = i2c_out(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CONTRL, 1, &b, 1);
}

void TSL2591_Enable(int state)
{
  int i;
  unsigned char b;
  
  if (state = 0)
    b = 0x00;
  if (state = 1)
    b = 0x03;
  
  i = i2c_out(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_ENABLE, 1, &b, 1);
}

void TSL2591_SetGain(int gain)
{
  int i;
  unsigned char b;
  
  i = i2c_in(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CONTRL, 1, &b, 1);

  b = b & 0xcf;
  b = b | gain << 4;
  
  i = i2c_out(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CONTRL, 1, &b, 1);
}

void TSL2591_SetIntegration(int time)
{
  int i;
  unsigned char b;
  
  i = i2c_in(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CONTRL, 1, &b, 1);
  
  b = b & 0xf8;
  b = b | time;
  
  i = i2c_out(tsl, TSL2591_ADDR, TSL2591_CMD | TSL2591_CONTRL, 1, &b, 1);
}

