/**
 * @brief BME680 Environmental Sensor
 * @author Michael Burmeister
 * @date December 7, 2019
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "BME680.h"

void _writeByte(unsigned char , unsigned char );
unsigned char _readByte(unsigned char);
void _readBytes(unsigned char , unsigned char , unsigned char *);
unsigned char getCalibrationData(void);

struct 
{
  unsigned short h1;
  unsigned short h2;
  unsigned char h3;
  unsigned char h4;
  unsigned char h5;
  unsigned char h6;
  unsigned char h7;
  
  unsigned char g1;
  unsigned short g2;
  unsigned char g3;
  
  unsigned short t1;
  unsigned short t2;
  unsigned char t3;
  
  unsigned short p1;
  unsigned short p2;
  unsigned char p3;
  unsigned short p4;
  unsigned short p5;
  unsigned char p6;
  unsigned char p7;
  unsigned short p8;
  unsigned short p9;
  unsigned char p10;
  
  int t_fine;
  unsigned char res_heat_range;
  unsigned char res_heat_val;
  unsigned char range_sw_err;
} BME680_Cal;
  
i2c _bme;
unsigned char _Address;

unsigned char BME680_init(unsigned char CLK, unsigned char DTA)
{
  int i;
  
  i2c_open(&_bme, CLK, DTA, 0);
  _Address = BME680_I2C_ADDR_SECONDARY;
  
  pause(100);
  i = BME680_getID();
  printi("%x\n", i);
  if (i != BME680_CHIP_ID)
    return -1;
  BME680_reset();
  return i;
}  

unsigned char BME680_reset()
{
  _writeByte(BME680_SOFT_RESET_ADDR, 0xff);
  
}  

unsigned char BME680_getID()
{
  return _readByte(BME680_CHIP_ID_ADDR);
}

unsigned char getCalibrationData()
{
  unsigned char Cal[BME680_COEFF_SIZE];
  unsigned char t;
  
  _readBytes(BME680_COEFF_ADDR1, BME680_COEFF_ADDR1_LEN, Cal);
  _readBytes(BME680_COEFF_ADDR2, BME680_COEFF_ADDR2_LEN, &Cal[BME680_COEFF_ADDR1_LEN]);
  
  BME680_Cal.t2 = (unsigned short)Cal[2] << 8 | Cal[1];
  BME680_Cal.t3 = Cal[3];
  BME680_Cal.p1 = (unsigned short)Cal[6] << 8 | Cal[5];
  BME680_Cal.p2 = (unsigned short)Cal[8] << 8 | Cal[7];
  BME680_Cal.p3 = Cal[9];
  BME680_Cal.p4 = (unsigned short)Cal[12] << 8 | Cal[11];
  BME680_Cal.p5 = (unsigned short)Cal[14] << 8 | Cal[13];
  BME680_Cal.p7 = Cal[15];
  BME680_Cal.p6 = Cal[16];
  BME680_Cal.p8 = (unsigned short)Cal[20] << 8 | Cal[19];
  BME680_Cal.p9 = (unsigned short)Cal[22] << 8 | Cal[21];
  BME680_Cal.p10 = Cal[23];
  BME680_Cal.h2 = (unsigned short)Cal[25] << 4 | (Cal[26] & 0x0f);
  BME680_Cal.h1 = (unsigned short)Cal[27] << 4 | (Cal[26] >> 4);
  BME680_Cal.h3 = Cal[28];
  BME680_Cal.h4 = Cal[29];
  BME680_Cal.h5 = Cal[30];
  BME680_Cal.h6 = Cal[31];
  BME680_Cal.h7 = Cal[32];
  BME680_Cal.t1 = (unsigned short)Cal[34] << 8 | Cal[33];
  BME680_Cal.g2 = (unsigned short)Cal[36] << 8 | Cal[35];
  BME680_Cal.g1 = Cal[37];
  BME680_Cal.g3 = Cal[38];
  
  t = _readByte(BME680_ADDR_RES_HEAT_RANGE_ADDR);
//  BME680_Cal.res_heat_range = (t & BME680_RHRANGE_MSK) / 16;
}
  
/**
 * @brief I2C read write routines
 * @param address device address to write to
 * @param subAddress device register or location on device
 * @param data to write
*/
void _writeByte(unsigned char subAddress, unsigned char data)
{
  i2c_out(&_bme, _Address, subAddress, 1, &data, 1);
}

/**
 * @brief I2C read routine
 * @param address address of device
 * @param subAddress device register or location on device
 * @return byte value
*/
uint8_t _readByte(unsigned char subAddress)
{
  uint8_t data;
  i2c_in(&_bme, _Address, subAddress, 1, &data, 1);
  return data;
}

/**
 * @brief I2C read routine
 * @param address of device
 * @param subAddress device register or location on device
 * @param cnt number of bytes to read
 * @param dest returned byte of data from device
*/
void _readBytes(unsigned char subAddress, unsigned char cnt, unsigned char *dest)
{
  i2c_in(&_bme, _Address, subAddress, 1, dest, cnt);
}
