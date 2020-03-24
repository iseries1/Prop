/**
 * @brief Read Barometric Pressure Sensor
 * @author Michael Burmeister
 * @date January 25, 2016
 * @version 1.1
 * 
*/

#include "simpletools.h"

void ms5607(void *par);
int Send_Cmd(i2c *, int );
void Get_Prom(i2c *);

#define DEVICE_ADDR 0xec
#define CMD_READ_ADC 0x00
#define CMD_RESET 0x1e
#define CMD_CONV_ADC 0x40
#define CMD_READ_PROM 0xa0

#define RSLT_D1 0x00
#define RSLT_D2 0x10

#define RES_256 0x00
#define RES_512 0x02
#define RES_1024 0x04
#define RES_2048 0x06
#define RES_4096 0x08

i2c msBus;
long long mC[8];
long D1, D2;
int mscog;
int msclk;
int mssda;


// Open Connection to device
int ms5607_open(int clk, int sda)
{
  int *i;
  
  msclk = clk;
  mssda = sda;
  
  i = cog_run(&ms5607, 100);
  return cog_num(i);
}

// Cog Function
void ms5607(void *par)
{
  int i;
  long d;
  
  i2c_open(&msBus, msclk, mssda, 0);
  
  mscog = -1;
  Get_Prom(&msBus);
  
  
  while (mscog)
  {
    pause(5000);
    i = Send_Cmd(&msBus, CMD_CONV_ADC | RSLT_D1);
    pause(50);
    i = Send_Cmd(&msBus, CMD_READ_ADC);
    i = i2c_poll(&msBus, DEVICE_ADDR | 1);
    d = i2c_readByte(&msBus, 0);
    d = (d << 8) | i2c_readByte(&msBus, 0);
    D1 = (d << 8) | i2c_readByte(&msBus, 1);
    i2c_stop(&msBus);
    pause(5000);
    i = Send_Cmd(&msBus, CMD_CONV_ADC | RSLT_D2);
    pause(50);
    i = Send_Cmd(&msBus, CMD_READ_ADC);
    i = i2c_poll(&msBus, DEVICE_ADDR | 1);
    d = i2c_readByte(&msBus, 0);
    d = (d << 8) | i2c_readByte(&msBus, 0);
    D2 = (d << 8) | i2c_readByte(&msBus, 1);
    i2c_stop(&msBus);
    
  }

  cogstop(cogid());
}

// Send an I2C command to the sensor
int Send_Cmd(i2c *b, int Cmd)
{
  int i = i2c_poll(b, DEVICE_ADDR);
  i = i2c_writeByte(b, Cmd);
  i2c_stop(b);
  return i;
}

// get configuration data from chip
void Get_Prom(i2c *b)
{
  int addr;
  int h;
  int l;
  Send_Cmd(b, CMD_RESET);
  pause(50);
  for (int j=0;j<8;j++)
  {
    addr = j << 1;
    l = Send_Cmd(b, CMD_READ_PROM | addr);
    pause(50);
    l = i2c_poll(b, DEVICE_ADDR | 1);
    h = i2c_readByte(b, 0) << 8;
    l = i2c_readByte(b, 0) | h;
    i2c_stop(b);
    mC[j] = l;
  }
}

// Close Connection to device
void ms5607_close(void)
{
  mscog = 0;
}

// Get Temperature
int ms5607_celsius(void)
{
  long long td, cels, t2;
  int C;
  
  t2 = 0;
  td = D2 - mC[5] * 256;
  cels = 2000 + td * mC[6] / 8388608;
  C = (int)cels;
  if (C < 2000)
  {
    t2 = td * td / 2147483648;
  }
  C = C - t2;
  C = C / 10;
  return C;
}

// Get Fahrenheit
int ms5607_fahrenheit(void)
{
  int i;
  
  i = ms5607_celsius();
  i = (i * 18 + 3200) / 100;
  return i;
}

// Get Pressure in Millibars
int ms5607_pressure(void)
{
  int i;
  long long td, cels;
  long long Poff, Psens;
  long long Poff2, Psens2;
  
  Poff2 = 0;
  Psens2 = 0;
  td = D2 - mC[5] * 256;
  cels = 2000 + td * mC[6] / 8388608;
  Poff = mC[2] * 131072 + mC[4] * td / 64;
  Psens = mC[1] * 65536 + (mC[3] * td) / 128;
  if (cels < 2000)
  {
    Poff2 = 61 * (cels - 2000) ^ 2 / 16;
    Psens2 = 2 * (cels - 2000) ^ 2;
  }
  Poff = Poff - Poff2;
  Psens = Psens - Psens2;
  i = (D1 * Psens / 2097152 - Poff) / 32768;
  return i;
}

// Get Pressure in Inches of Mercury
int ms5607_mercury(void)
{
  int i;
  
  i = ms5607_pressure();
  i = i * 295 / 10000;
  return i;
}

// Get Raw Temp
int ms5607_rawtemp(void)
{
  return D2;
}

// Get Raw Pressure
int ms5607_rawpressure(void)
{
  return D1;
}

// Math Test (107/51 95704/2823)
void ms5607_set(void)
{
    D1 = 6215136;
    D2 = 7897952;
    mC[1] = 45325;
    mC[2] = 42747;
    mC[3] = 27968;
    mC[4] = 26338;
    mC[5] = 31913;
    mC[6] = 27457;
}
      