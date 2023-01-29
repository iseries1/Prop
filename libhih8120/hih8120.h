/**
 * @file hih8120.h
 * @brief Honeywell Humidity and Temperature chip
 * @author Michael Burmeister
 * @date January 16, 2016
 * @version 1.1
 * 
*/

#ifndef HIH8120_H
#define HIH8120_H

#include "simplei2c.h"


#define MSingle 0x01

/**
 * @brief Open connection to hih8120
 *
 * @param SCL i2c Clock Pin
 * @param SDA i2c Data Pin
 * @return Cog number of compass connection
*/
int hih8120_open(int SCL, int SDA);

/**
 * @brief Close connection to hih8120 free cog
 *
 * @return Nothing
*/
void hih8120_close(void);

/**
 * @brief humidity percentage times 100
 *
 * @return humidity percent
*/
int hih8120_humidity(void);

/**
 * @brief temperature in celsius times 10
 *
 * @return temperature
*/
int hih8120_celsius(void);

/**
 * @brief temperature in fahrenheit
 *
 * @return temperature
*/
int hih8120_fahrenheit(void);

/**
 * @brief raw humidity value
 *
 * @return humidity
*/
int hih8120_rawhumidity(void);

/**
 * @brief raw temperature value
 *
 * @return temperature
*/
int hih8120_rawtemperature(void);

/**
 * @brief get status of operation
 *
 * @return status
*/
int hih8120_status(void);

#endif
