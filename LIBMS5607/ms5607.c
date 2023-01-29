/**
 * @brief MS5607 pressure drive
 * @author Michael Burmeister
 * @date May 24, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "simplei2c.h"
#include "ms5607.h"
#include "ms5607reg.h"

int readWord(int);
int readLong(int);


i2c msBus;
static int man;
static int C1;
static int C2;
static int C3;
static int C4;
static int C5;
static int C6;
static int CX;
static int OSR;

int ms5607_init(int scl, int sda, int osr)
{
  int i;
  
  i2c_open(&msBus, scl, sda, 0);
  OSR = osr;
  
  i = i2c_poll(&msBus, DEVICE_ADDR);
  if (i != 0)
    return 0;
  i2c_writeByte(&msBus, CMD_RESET);
  pause(50);
  man = readWord(CMD_READ_PROM);
  C1 = readWord(CMD_READ_PROM | 2);
  C2 = readWord(CMD_READ_PROM | 4);
  C3 = readWord(CMD_READ_PROM | 6);
  C4 = readWord(CMD_READ_PROM | 8);
  C5 = readWord(CMD_READ_PROM | 10);
  C6 = readWord(CMD_READ_PROM | 12);
  CX = readWord(CMD_READ_PROM | 14);
  CX = CX & 0x0f;
  return CX;
}

void ms5607_close()
{
  i2c_stop(&msBus);
}

int ms5607_rawtemperature(void)
{
  int D2;
  
  D2 = readLong(CMD_CONV_ADC | RSLT_D2 | OSR);
  
  return D2;
}

int ms5607_rawpressure(void)
{
  int D1;
  
  D1 = readLong(CMD_CONV_ADC | RSLT_D1 | OSR);
  
  return D1;
}

int ms5607_temperature(void)
{
  int i;
  long long dt, t;

  i = ms5607_rawtemperature();
  dt = i - C5 * 256;
  t = 2000 + dt * C6 / 8388608;
  if (dt < 0)
    t = t - dt * dt / 2147483648; 
  i = t;
  return i;
}

int ms5607_fahrenheit(void)
{
  int i;
  
  i = ms5607_temperature();
  i = (i * 18 + 32000) / 10;
  return i;
}

int ms5607_pressure(void)
{
  long long offset, sens, t, dt;
  int i;
  
  i = ms5607_rawtemperature();
  dt = i - C5 * 256;
  t = dt * C6 / 8388608;
  offset = C2;
  offset = offset * 131072 + (C4 * dt) / 64;
  if (dt < 0)
    offset = offset - (61 * t * t / 16);
  sens = C1;
  sens = sens * 65536 + (C3 * dt) / 128;
  if (dt < 0)
    sens = sens - (2 * t * t);
  i = ms5607_rawpressure();
  i = (i * sens / 2097152 - offset) / 32768;
  return i;
}

int ms5607_mercury(void)
{
  int i;
  
  i = ms5607_pressure();
  i = i * 295 / 10000;
  return i;
}


/*
 * read word from device
 */  
int readWord(int address)
{
  int i;
  
  i = i2c_poll(&msBus, DEVICE_ADDR);
  i2c_writeByte(&msBus, address);
  i2c_stop(&msBus);
  i = i2c_poll(&msBus, DEVICE_ADDR | 1);
  i = i2c_readByte(&msBus, 0);
  i = i << 8 | i2c_readByte(&msBus, 1);
  return i;
}

/*
 * read 24 bit value
 */
int readLong(int address)
{
  int i;
  
  i = i2c_poll(&msBus, DEVICE_ADDR);
  i2c_writeByte(&msBus, address);
  i2c_stop(&msBus);
  pause(10);
  i = i2c_poll(&msBus, DEVICE_ADDR);
  if (i == 0)
  {
    i2c_poll(&msBus, DEVICE_ADDR);
    i2c_writeByte(&msBus, CMD_READ_ADC);
    i2c_stop(&msBus);
    i2c_poll(&msBus, DEVICE_ADDR | 1);
    i = i2c_readByte(&msBus, 0);
    i = i << 8 | i2c_readByte(&msBus, 0);
    i = i << 8 | i2c_readByte(&msBus, 1);
  }
  i2c_stop(&msBus);
  return i;    
}  