/**
 * @brief INA260 Adafruit power driver
 * @author Michael Burmeister
 * @date June 23, 2019
 * @version 1.0
 * 
*/

#include "ina260_reg.h"
#include "ina260.h"
#include "simpletools.h"


void _writeWord(unsigned char register, unsigned short data);
unsigned short _readWord(unsigned char register);

unsigned char _INA260;
i2c _INA260C;


unsigned short INA260_open(char clock, char data)
{
  unsigned short id;
  
  _INA260 = INA260_I2CADDR;

  i2c_open(&_INA260C, clock, data, 0);
  
  id = _readWord(INA260_MFGID);
  return id;
}

short INA260_getCurrent(void)
{
  short v;
  int c;
  
  v = _readWord(INA260_CURRENT);

  c = v * 125 / 100;
  
  return c;
}

short INA260_getVoltage(void)
{
  int v;
  
  v = _readWord(INA260_VOLTAGE);
  v = v * 125;
  
  return v/100;
}

short INA260_getPower(void)
{
  int v;
  
  v = _readWord(INA260_POWER);
  v = v * 10;

  return v;
}

void INA260_setMode(int mode)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0xfff8;
  v = v | mode;

  _writeWord(INA260_CONFIG, v);
}

int INA260_getMode(void)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0x07;

  return v;
}

void INA260_configCurrent(int time)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0xffc7;
  v = v | (time << 3);

  _writeWord(INA260_CONFIG, v);
}

int INA260_getConfigCurrent(void)
{
  int i;
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0x0038;
  v = v >> 3;
  return v;
}

void INA260_configVoltage(int time)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0xfe3f;
  v = v | (time << 6);

  _writeWord(INA260_CONFIG, v);
}

int INA260_getConfigVoltage(void)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0x01c0;
  v = v >> 6;
  return v;
}

void INA260_configAveraging(int number)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0xf1ff;
  v = v | (number << 9);

  _writeWord(INA260_CONFIG, v);
}

int INA260_getConfigAveraging(void)
{
  int v;

  v = _readWord(INA260_CONFIG);

  v = v & 0x0e00;
  v = v >> 9;

  return v;
}

void INA260_setMask(unsigned short mask)
{
  int v;
  
  v = 1 << (mask + 10);
  _writeWord(INA260_ALERTEN, v);
  
}

unsigned short INA260_getMask(void)
{
  unsigned short v;
  
  v = _readWord(INA260_ALERTEN);
  
  return v;
}

void INA260_setAlert(unsigned short alert)
{
  _writeWord(INA260_ALERTV, alert);
}

int INA260_getAlert(void)
{
  int v;

  v = _readWord(INA260_ALERTV);

  return v;
}

void INA260_reset(void)
{
  int i;

  _writeWord(INA260_CONFIG, 0x80);
}


/* basic read write funcitons
 */

/**
 * @brief I2C read write routines
 * @param reg register on device
 * @param data to write
*/
void _writeWord(unsigned char reg, unsigned short data)
{
  unsigned char v[2];
  
  v[0] = data >> 8;
  v[1] = data;
  
  i2c_out(&_INA260C, _INA260, reg, 1, v, 2);
}


/**
 * @brief I2C read routine
 * @param reg register on device
 * @return byte value
*/
unsigned short _readWord(unsigned char reg)
{
  unsigned short v;
  unsigned char data[2];
  
  i2c_in(&_INA260C, _INA260, reg, 1, data, 2);
  
  v = data[0] << 8 | data[1];
  
  return v;
}
