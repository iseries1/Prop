/**
 * @file compass.c
 * @author: Michael Burmeister
 * @date: April 12, 2014
 * @version: 1.1
 * @brief 29133 Compass Module HMC5883L
 */

#include "simpletools.h"
#include "compass.h"


void Compass(void *par);


int MSCL, MSDA, MMode, MGain, MCompass;
static volatile long Xa, Ya, Za;
i2c bus, *pbus;


// Mode is single or continues or Standby
int Compass_Open(int Clk, int Data, int Mod)
{
  int *i;
  MSCL = Clk;
  MSDA = Data;
  MMode = Mod;
  MCompass = -1;
  i = cog_run(&Compass, 100);
  return cog_num(i);
}

// Cog Function
void Compass(void *par)
{
  unsigned char b[10];
  short X, Y, Z;
  unsigned char G;
  int i, a;

  G = 1;
  G = G << 5;
  a = MAdd >> 1;
  pbus = i2c_open(&bus, MSCL, MSDA, 0);
  b[0] = MMode;
  i = MModr;
  i2c_out(pbus, a, i, 1, b, 1);

  Xa = 0;
  Ya = 0;
  Za = 0;
  
  while (MCompass)
  {
    b[0] = MStatus;
    i = MStatus;
    i2c_in(pbus, a, i, 1, b, 1);
    if ((b[0] & 1) != 0)
    {
      i = MDReg;
      i2c_in(pbus, a, i, 1, b, 6);
      X = (b[0] << 8) | b[1]; 
      Z = (b[2] << 8) | b[3];
      Y = (b[4] << 8) | b[5];
      if (abs(Xa-X) > 2)
        Xa = X;
      if (abs(Ya-Y) > 2)
        Ya = Y;
      if (abs(Za-Z) > 2)
        Za = Z;
    }
    if (MGain != G)
    {
      b[0] = MGain;
      i = MConfb;
      i2c_out(pbus, a, i, 1, b, 1);
      MGain = G;
    }      
  }
  cogstop(cogid());
}

// Set the Gain 0 - 7
void Compass_SetGain(int g)
{
    MGain = g << 5;
}

// Read gain value
int Compass_GetGain()
{
  return MGain >> 5;
}  

// Shutdown Compass Cog
void Compass_Close()
{
  MCompass = 0;
}

// Get average compass values
void Compass_Read(int *x, int *y, int *z)
{
  *x = Xa;
  *y = Ya;
  *z = Za;
}
  