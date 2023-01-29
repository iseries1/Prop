/**
 * @brief Device Driver for LIS3DH
 * @author Michael Burmeister
 * @date May 8, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "lis3dh.h"
#include "lis3dhreg.h"


char lis3dh_read(int);
void lis3dh_readBytes(int, char *, int);
int lis3dh_readWord(int);
void lis3dh_write(int, int);

static int SCK;
static int SDI;
static int SDO;
static int SCS;


int lis3dh_init(int sck, int sdi, int sdo, int scs)
{
  int i;
  
  SCK = sck;
  SDI = sdi;
  SDO = sdo;
  SCS = scs;
  
  high(SCS);
  high(SDI);
  input(SDO);
  lis3dh_write(CTRL_REG4, 0x80);
  i = lis3dh_whoAmI();
  return i;
}

int lis3dh_whoAmI(void)
{
  int i;
  
  i = lis3dh_read(WHO_AM_I);
  return i;
}

void lis3dh_updateRate(int rate)
{
  int i;
  
  i = lis3dh_read(CTRL_REG1);
  i = i & 0xf;
  i |= rate << 4;
  lis3dh_write(CTRL_REG1, i);
}

void lis3dh_enableADC(void)
{
  int i;
  
  i = lis3dh_read(TEMP_CFG_REG);
  i |= 0x80;
  lis3dh_write(TEMP_CFG_REG, i);
}

int lis3dh_readADC1(void)
{
  int i;
  
  i = lis3dh_readWord(OUT_ADC1);
  return i;
}

unsigned char lis3dh_status(void)
{
  int i;
  
  i = lis3dh_read(STATUS_REG);
  return i;
}

void lis3dh_axis(short *x, short *y, short *z)
{
  int i;
  
  *x = lis3dh_readWord(OUT_X);
  *y = lis3dh_readWord(OUT_Y);
  *z = lis3dh_readWord(OUT_Z);
}

void lis3dh_range(int range)
{
  int i;
  
  i = lis3dh_read(CTRL_REG4);
  i = i & 0xcf;
  i = i | range << 4;
  lis3dh_write(CTRL_REG4, i);
}

/**
 * Read/Write functions
 */

char lis3dh_read(int address)
{
  int a;
  
  a = 0x80 | address;
  low(SCS);
  shift_out(SDI, SCK, MSBFIRST, 8, a);
  a = shift_in(SDO, SCK, MSBPRE, 8);
  high(SCS);
  return a;
}

void lis3dh_readBytes(int address, char *data, int len)
{
  int a;
  
  a = 0xc0 | address;
  low(SCS);
  shift_out(SDI, SCK, MSBFIRST, 8, a);
  for (int i=0;i<len;i++)
  {
    data[i] = shift_in(SDO, SCK, MSBPRE, 8);
  }
  high(SCS);
}

int lis3dh_readWord(int address)
{
  int a;
  
  a = 0xc0 | address;
  low(SCS);
  shift_out(SDI, SCK, MSBFIRST, 8, a);
  a = shift_in(SDO, SCK, MSBPRE, 8);
  a |= shift_in(SDO, SCK, MSBPRE, 8) << 8;
  high(SCS);
  return a;
}

void lis3dh_write(int address, int data)
{
  int a;
  
  a = address;
  low(SCS);
  shift_out(SDI, SCK, MSBFIRST, 8, a);
  shift_out(SDI, SCK, MSBFIRST, 8, data);
  high(SCS);
}
