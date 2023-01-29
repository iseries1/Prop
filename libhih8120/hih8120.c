/**
 * @file hih8120.c
 * @brief Honeywell Humidity and Temperature chip
 * @author Michael Burmeister
 * @date January 16, 2016
 * @version 1.1
 * 
*/

#include "simpletools.h"
#include "hih8120.h"

#define daddress 0x27
#define ACK 0
#define NACK 1

void Hih8120(void *par);

i2c hih8120;
int RAdd;
int WAdd;
int hsclk;
int hsda;
int htemp;
int hhumidity;
int hstatus;
int hihcog;


// open connection to sensor
int hih8120_open(int SCLK, int SDA)
{
  int *i;
  
  RAdd = daddress << 1 | 1;
  WAdd = daddress << 1 & 254;
  hsclk = SCLK;
  hsda = SDA;
  htemp = -1;
  hhumidity = -1;
  hstatus = -1;
    
  i = cog_run(&Hih8120, 100);
  return cog_num(i);
}

// Cog Function
void Hih8120(void *par)
{
  int i, j;
  int r = -1;
  
  i2c_open(&hih8120, hsclk, hsda, 0);
  
  hihcog = -1;
  
  while (hihcog)
  {
    pause(10000);
    r = i2c_poll(&hih8120, WAdd);  //Measurement request
    i2c_stop(&hih8120);
    pause(50);
    
    if (r == ACK)
    {
      i = i2c_poll(&hih8120, RAdd);  //Read Request
      i = i2c_readByte(&hih8120, ACK);  //High bits
      hstatus = i & 0xc0;  //First two bits
      i = i & 0x3f;  //6 bits of humidity
      j = i << 8;
      i = i2c_readByte(&hih8120, ACK); //Read lower 8 bits and send ACK
      j += i;
      hhumidity = j;
      
      i = i2c_readByte(&hih8120, ACK); //Read high 8 bits and send ACK
      j = i << 8;
      i = i2c_readByte(&hih8120, NACK); //Read lower 8 bits and send NACK
      i2c_stop(&hih8120);
      j = j + i;
      j = j >> 2; //Drop last 2 bits not used
      htemp = j;
    }
    else
      hstatus = -1;
  }
  cogstop(cogid());
}

// close connection
void hih8120_close()
{
  hihcog = 0;
}

// get humidity percentage times 100
int hih8120_humidity()
{
  int i;
  
  i = hhumidity;
  i = i * 100 / 16382;
  return i;
}

// get temperature in celsius in tenths
int hih8120_celsius()
{
  int i;
  
  i = htemp * 1650 / 16382 - 400;
  return i;
}

// get temperature in fahrenheit
int hih8120_fahrenheit()
{
  int i;
  
  i = hih8120_celsius();
  i = (i * 18 + 3200)/100;
  return i;
}

int hih8120_rawhumidity()
{
  return hhumidity;
}

int hih8120_rawtemperature()
{
  return htemp;
}

int hih8120_status()
{
  return hstatus;
}
