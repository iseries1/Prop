/**
 * @file gyro.c
 * @brief Using Gyroscope module L3G4200D
 * @author Michael Burmeister
 * @date January 5, 2014
 * @version 1.0
 */

#include "simpletools.h"
#include "gyro.h"

void Gyro_Loop(void *par);
int Gyro_Read(int cmd);
int Gyro_Write(int cmd, int data);
void Gyro_Offset(void);


#define Address 0xD2
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define Reference 0x25
#define WHOAMI 0x0F
#define Temp 0x26
#define Status 0x27
#define Out 0x28
#define ZYXDA 0x08
#define ZYXOR 0x80
#define Mode 0x1F
#define Avg 32
#define Noise 114;


i2c Bus;
i2c *pbus;
int GSCL;
int GSDA;
int Ax[Avg];
int Ay[Avg];
int Az[Avg];
int Avx;
int Avy;
int Avz;
int ox, oy, oz;
int Ind;
int over;
int GyroCog;


// Open Gyro Connection
int Gyro_Open(int SCL, int SDA)
{
  int *i;
  
  GSCL = SCL;
  GSDA = SDA;
  
  i = cog_run(&Gyro_Loop, 80);
  
  pause(100);
  if (Gyro_Status() < 0)
      return -2;

  pause(1000);
  Gyro_Offset();
  return cog_num(i);
}

int Gyro_Status(void)
{
  if (GyroCog == 0)
    return -1;
  if (over > 0)
  {
      over = 0;
      return 1;
  }
  return 0;
}
     
void Gyro_Loop(void *par)
{
  int i;
  short x, y, z;
  GyroCog = 0;
  pbus = NULL;
  ox = 0;
  oy = 0;
  oz = 0;
  
  pbus = i2c_open(&Bus, GSCL, GSDA, 0);
  if (pbus == NULL)
      return;
  i = Gyro_Read(WHOAMI);
  if (i != 0xd3)
      return;
  Gyro_Write(CTRL_REG3, ZYXDA);
  Gyro_Write(CTRL_REG5, 0x40);
  Gyro_Write(CTRL_REG1, Mode);
  
  GyroCog = -1;
  Ind = 0;
  Avx = 0;
  Avy = 0;
  Avz = 0;
  memset(Ax, 0, sizeof(Ax));
  memset(Ay, 0, sizeof(Ay));
  memset(Az, 0, sizeof(Az));

  while (GyroCog)
  {
    i = Gyro_Read(Status);
    if ((i & ZYXDA) != 0)
    {
      if ((i & ZYXOR) != 0)
          over = 1;
      
      i = i2c_poll(pbus, Address);
      if (i == 0)
      {
        i = i2c_writeByte(pbus, Out | 0x80); //read multiple registers
        if (i == 0)
        {
          i2c_poll(pbus, Address | 1);
          x = i2c_readByte(pbus, 0);
          x = x | i2c_readByte(pbus, 0) << 8;
          y = i2c_readByte(pbus, 0);
          y = y | i2c_readByte(pbus, 0) << 8;
          z = i2c_readByte(pbus, 0);
          z = z | i2c_readByte(pbus, 1) << 8;
          i2c_stop(pbus);
          
          Avx += x;
          Avy += y;
          Avz += z;
          Avx -= Ax[Ind];
          Avy -= Ay[Ind];
          Avz -= Az[Ind];
          Ax[Ind] = x;
          Ay[Ind] = y;
          Az[Ind++] = z;
          if (Ind >= Avg)
              Ind = 0;
          pause(1);
        }          
      }        
    }      
  }
  cogstop(cogid());  
}

// Issue Gyro Command with Read 
int Gyro_Read(int cmd)
{
  int i;
  
  i = i2c_poll(pbus, Address);
  if (i != 0)
      return -1;
  i = i2c_writeByte(pbus, cmd);
  if (i != 0)
      return -1;
  i2c_poll(pbus, Address | 1);
  i = i2c_readByte(pbus, 1);
  i2c_stop(pbus);
  return i;
}

// Issue Gyro Command with Write
int Gyro_Write(int cmd, int data)
{
  int i;
  
  i = i2c_poll(pbus, Address);
  if (i != 0)
      return -1;
  i = i2c_writeByte(pbus, cmd);
  if (i != 0)
      return -1;
  i = i2c_writeByte(pbus, data);
  i2c_stop(pbus);
  return i;
}

// Get average Gyro Readings
void Gyro_ReadXYZ(int *x, int *y, int *z)
{
  *x = (Avx/Avg-ox)/Noise;
  *y = (Avy/Avg-oy)/Noise;
  *z = (Avz/Avg-oz)/Noise;
}

// Save Average at rest
void Gyro_Offset(void)
{
  ox = Avx/Avg;
  oy = Avy/Avg;
  oz = Avz/Avg;
}
  
// Shutdown
void Gyro_Close(void)
{
  GyroCog = 0;
}

  