/**
 * @brief Sparkfun 9DOF board
 * @author Michael Burmeister
 * @date August 31, 2017
 * @version 1.0
 * 
 */

#include "simpletools.h"
#include "lsm9ds1.h"
#include "lsm9ds1reg.h"

void WriteByte(unsigned char, unsigned char, unsigned char);
unsigned char ReadByte(unsigned char, unsigned char);
void ReadBytes(unsigned char, unsigned char, unsigned char, unsigned char *);

i2c *lsm;
char _Buffer[10];
short Aax, Aay, Aaz;
short Agx, Agy, Agz;

unsigned char LSMInit(short scl, short sda)
{
  Aax = 0;
  Aay = 0;
  Aaz = 0;
  Agx = 0;
  Agy = 0;
  Agz = 0;
  lsm = i2c_newbus(scl, sda, 0);
  pause(250);
  return AccelGyroSignature();
}

unsigned char AccelGyroSignature()
{
  ReadByte(LSM9DS1Address, WHO_AM_I_XG);
  return ReadByte(LSM9DS1Address, WHO_AM_I_XG);
}

unsigned char AccelGyroReady()
{
  return ReadByte(LSM9DS1Address, STATUS_REG_1);
}

unsigned char MagReady()
{
  char i;
  i = ReadByte(LSM9DS1Address, STATUS_REG_M);
  i = i & 0x04;
  return i;
}
  
void setOrientation(unsigned char range)
{
  WriteByte(LSM9DS1Address, ORIENT_CFG_G, range);
}

void readAccel(short* ax, short* ay, short* az)
{
  ReadBytes(LSM9DS1Address, OUT_X_L_XL, 6, _Buffer);
  *ax = ((short)_Buffer[1] << 8) | _Buffer[0];
  *ay = ((short)_Buffer[3] << 8) | _Buffer[2];
  *az = ((short)_Buffer[5] << 8) | _Buffer[4];
  *ax += Aax;
  *ay += Aay;
  *az += Aaz;
}       

void readGyro(short *gx, short *gy, short *gz)
{
  ReadBytes(LSM9DS1Address, OUT_X_L_G, 6, _Buffer);
  *gx = ((short)_Buffer[1] << 8) | _Buffer[0];
  *gy = ((short)_Buffer[3] << 8) | _Buffer[2];
  *gz = ((short)_Buffer[5] << 8) | _Buffer[4];
  *gx += Agx;
  *gy += Agy;
  *gz += Agz;
}

void readMag(short *mx, short *my, short *mz)
{
  ReadBytes(LSM9DS1MagAddress, OUT_X_L_M, 6, _Buffer);
  *mx = ((short)_Buffer[1] << 8) | _Buffer[0];
  *my = ((short)_Buffer[3] << 8) | _Buffer[2];
  *mz = ((short)_Buffer[5] << 8) | _Buffer[4];
}

unsigned char MagSignature()
{
  return ReadByte(LSM9DS1MagAddress, WHO_AM_I_M);
}

void setAccelRange(unsigned char range)
{
  range = range << 3;
  WriteByte(LSM9DS1Address, CTRL_REG5_XL, 0x38); // enable x, y, and z
  WriteByte(LSM9DS1Address, CTRL_REG6_XL, range);
}

void setGyroRange(unsigned char range)
{
  range = (range << 3);
  WriteByte(LSM9DS1Address, CTRL_REG1_G, range);
  WriteByte(LSM9DS1Address, CTRL_REG2_G, 0x00); // no interrupts
  WriteByte(LSM9DS1Address, CTRL_REG3_G, 0x00); // normal power mode
  WriteByte(LSM9DS1Address, CTRL_REG4, 0x38); // enable x, y, and z
}

void setMagRange(unsigned char range)
{
  range = (range << 5) | 0x00;
  WriteByte(LSM9DS1MagAddress, CTRL_REG2_M, range);
}

void setGyroRate(unsigned char range)
{
  unsigned char W = ReadByte(LSM9DS1Address, CTRL_REG1_G);
  range = (range << 5) | (W & 0x1F);
  WriteByte(LSM9DS1Address, CTRL_REG1_G, range);
}

void setGyroBW(unsigned char range)
{
  unsigned char W = ReadByte(LSM9DS1Address, CTRL_REG1_G);
  range = (W & 0xFC) | range;
  WriteByte(LSM9DS1Address, CTRL_REG1_G, range);
}
  
unsigned char getAccelRate()
{
  return ReadByte(LSM9DS1Address, CTRL_REG1_G);
}

unsigned char getGyroRate()
{
  return ReadByte(LSM9DS1Address, CTRL_REG1_G);
}

void setAccelRate(uint8_t range)
{
  unsigned char W = ReadByte(LSM9DS1Address, CTRL_REG6_XL);
  range = (range << 5) | (W & 0x1F);
  WriteByte(LSM9DS1Address, CTRL_REG6_XL, range);
}

void setMagRate(uint8_t range)
{
  range = (range << 2) | 0xC0;
  WriteByte(LSM9DS1MagAddress, CTRL_REG1_M, range);
  range = ReadByte(LSM9DS1MagAddress, CTRL_REG3_M);
  range = range & 0xfc; //continues conversion
  WriteByte(LSM9DS1MagAddress, CTRL_REG3_M, range);
}

short getTemperature()
{
  ReadBytes(LSM9DS1Address, OUT_TEMP_L, 2, _Buffer);
  short W = ((_Buffer[1] << 8) | _Buffer[0]);
  return W/16+25;
}

void setAccelOffset(short ax, short ay, short az)
{
  Aax = ax;
  Aay = ay;
  Aaz = az;
}

void setGyroOffset(short gx, short gy, short gz)
{
  Agx = gx;
  Agy = gy;
  Agz = gz;
}

void getGyroOffset(short *gx, short *gy, short *gz)
{
  long tgx, tgy, tgz;
  short x, y, z;
  int t;
  
  setGyroOffset(0, 0, 0);
  pause(250);
  readGyro(&x, &y, &z);
  t = 0;
  tgx = 0;
  tgy = 0;
  tgz = 0;
  
  while (t < 255)
  {
    if ((AccelGyroReady() & 0x02) == 2)
    {
      readGyro(&x, &y, &z);
      tgx += x;
      tgy += y;
      tgz += z;
      t++;
    }
  }
  *gx = -tgx / t;
  *gy = -tgy / t;
  *gz = -tgz / t;
}
            
// i2c read and write protocols
void WriteByte(unsigned char address, unsigned char subAddress, unsigned char data)
{
  i2c_out(lsm, address, subAddress, 1, &data, 1);
}

unsigned char ReadByte(unsigned char address, unsigned char subAddress)
{
  unsigned char data;
  i2c_in(lsm, address, subAddress, 1, &data, 1);
  return data;
}

void ReadBytes(unsigned char address, unsigned char subAddress, unsigned char cnt, unsigned char *dest)
{
  i2c_in(lsm, address, subAddress, 1, dest, cnt);
}
