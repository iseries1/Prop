/**
 * @file lis3dh.h
 * @brief Device Driver for LIS3DH
 * @author Michael Burmeister
 * @date May 8, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"

enum power
{
  POWER_DOWN,
  UP_1HZ,
  UP_10HZ,
  UP_25HZ,
  UP_50HZ,
  UP_100HZ,
  UP_200HZ,
  UP_400HZ
};

enum full_scale
{
  SCALE_2G,
  SCALE_4G,
  SCALE_8G,
  SCALE_16G
};
  
/**
 * @brief initilize lis3dh driver
 * @param sck spi clock pin
 * @param sdi spi data in pin
 * @param sdo spi data out pin
 * @param scs spi chip select
 * @return chip id
 */
int lis3dh_init(int sck, int sdi, int sdo, int scs);

/**
 * @brief get chip id 0x33
 * @return chip id
 */
int lis3dh_whoAmI(void);

/**
 * @brief set update rate
 * @param rate update rate value UP_1HZ
 */
void lis3dh_updateRate(int rate);

/**
 * @brief enable adc
 */
void lis3dh_enableADC(void);

/**
 * @brief get adc1 value
 * @return voltage
 */
int lis3dh_readADC1(void);

/**
 * @brief get status
 * @return status 
 */
unsigned char lis3dh_status(void);

/**
 * @brief get axis data
 * @param x - x axis value
 * @param y - y axis value
 * @param z - z axis value
 */
void lis3dh_axis(short *x, short *y, short *z);

/**
 * @brief set g force range
 * @param range g force range SCALE_2G, SCALE_4G, ...
 */
void lis3dh_range(int range);
