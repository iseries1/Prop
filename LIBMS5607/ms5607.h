/**
 * @file ms5607.h
 * @brief Read Barometric Pressure Sensor
 * @author Michael Burmeister
 * @date January 25, 2016
 * @version 1.1
 * @mainpage Custom Libraries
 * <a href="ms5607_8h.html">MS5607 Barometric Pressure Sensor.</a><br>
*/

#ifndef MS5607_H
#define MS5607_H

#include "simplei2c.h"

/**
 * @brief Open connection to ms5607
 *
 * @param SCL i2c Clock Pin
 * @param SDA i2c Data Pin
 * @return Cog number of compass connection
*/
int ms5607_open(int SCL, int SDA);

/**
 * @brief Close connection to ms5607
 *
 * @return Nothing
*/
void ms5607_close(void);

/**
 * @brief Get current tempreture in celsius
 *
 * @return Celsius
*/
int ms5607_celsius(void);

/**
 * @brief Get current tempreture in fahrenheit
 *
 * @return Fahrenheit
*/
int ms5607_fahrenheit(void);

/**
 * @brief Get current pressure in millibars
 *
 * @return Millibars
*/
int ms5607_pressure(void);

/**
 * @brief Get current pressure in hundredths of an Inch of Mercury
 *
 * @return Millibars
*/
int ms5607_mercury(void);

/**
 * @brief Get raw temperature
 *
 * @return Temp
*/
int ms5607_rawtemp(void);

/**
 * @brief Get raw pressure
 *
 * @return Pressure
*/
int ms5607_rawpressure(void);

#endif
