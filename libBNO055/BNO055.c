/**
 * @brief BOSCH BNO055 driver library
 * @author Michael Burmeister
 * @date March 14, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "BNO055.h"
#include "BNO055reg.h"
#include "fdserial.h"

int BNO055_writeByte(unsigned char , unsigned char );
int BNO055_readByte(unsigned char);
int BNO055_readBytes(unsigned char , unsigned char *, unsigned char);

fdserial *_sr;


int BNO055_init(int scl, int sda)
{
  int i;
  
  _sr = fdserial_open(sda, scl, 0, 115200);
  pause(100);
  i = BNO055_ID();
  return i;
}
  
int BNO055_ID(void)
{
  int i;
  
  i = BNO055_readByte(BNO055CHIPID);
  return i;
}

int BNO055_ACCID()
{
  int i;
  
  i = BNO055_readByte(BNO055ACCID);
  return i;
}

int BNO055_MAGID()
{
  int i;
  
  i = BNO055_readByte(BNO055MAGID);
  return i;
}

int BNO055_GYROID()
{
  int i;
  
  i = BNO055_readByte(BNO055GYROID);
  return i;
}  

int BNO055_OperatingMode(unsigned char mode)
{
  int i;
  
  i = BNO055_writeByte(BNO055OPRMODE, mode);
  return i;
}

int BNO055_getOperatingMode()
{
  int i;
  
  i = BNO055_readByte(BNO055OPRMODE);
  return i;
}

int BNO055_getEulerAngle(short *heading, short *roll, short *pitch)
{
  int i;
  unsigned char data[6];
  
  i = BNO055_readBytes(BNO055EULDATAXL, data, 6);
  *heading = data[0] | (data[1] << 8);
  *roll = data[2] | (data[3] << 8);
  *pitch = data[4] | (data[5] << 8);
  return i;
}

int BNO055_Temperature()
{
  int i;
  
  i = BNO055_readByte(BNO055TEMP);
  return i;
}

int BNO055_getCalibration()
{
  int i;
  
  i = BNO055_readByte(BNO055CALBSTATS);
  return i;
}
  
  
/**
 * @brief I2C read write routines
 * @param subAddress device register or location on device
 * @param data to write
*/
int BNO055_writeByte(unsigned char subAddress, unsigned char data)
{
  unsigned char Data;
  
  fdserial_txChar(_sr, 0xAA);
  fdserial_txChar(_sr, 0x00);
  fdserial_txChar(_sr, subAddress);
  fdserial_txChar(_sr, 0x01);
  fdserial_txChar(_sr, data);
  
  Data = fdserial_rxChar(_sr);
  if (Data == 0xEE)
  {
    Data = fdserial_rxChar(_sr);
    return -Data;
  }
  
  return 0;
}

/**
 * @brief I2C read routine
 * @param subAddress device register or location on device
 * @return byte value
*/
int BNO055_readByte(unsigned char subAddress)
{
  unsigned char Data;
  unsigned char Len;
  
  fdserial_txChar(_sr, 0xAA);
  fdserial_txChar(_sr, 0x01);
  fdserial_txChar(_sr, subAddress);
  fdserial_txChar(_sr, 0x01);

  Data = fdserial_rxChar(_sr);
  if (Data == 0xBB)
  {
    Len = fdserial_rxChar(_sr);
    Data = fdserial_rxChar(_sr);
  }
  else
  {
    Len = fdserial_rxChar(_sr);
    return -Len;
  }
  
  return Data;
}

/**
 * @brief I2C read routine
 * @param subAddress device register or location on device
 * @param dest returned byte of data from device
 * @param cnt number of bytes to read
*/
int BNO055_readBytes(unsigned char subAddress, unsigned char *dest, unsigned char cnt)
{
  unsigned char Data;
  unsigned char Len;
  
  fdserial_txChar(_sr, 0xAA);
  fdserial_txChar(_sr, 0x01);
  fdserial_txChar(_sr, subAddress);
  fdserial_txChar(_sr, cnt);

  Data = fdserial_rxChar(_sr);
  if (Data == 0xBB)
  {
    Len = fdserial_rxChar(_sr);
    for (int i=0;i<Len;i++)
      dest[i] = fdserial_rxChar(_sr);
  }
  else
  {
    Len = fdserial_rxChar(_sr);
    return -Len;
  }
  
  return 0;
}
