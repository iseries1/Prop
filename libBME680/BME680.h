/**
 * @file BME680.h
 * @brief BME680 Environmental Sensor
 * @author Michael Burmeister
 * @date December 7, 2019
 * @version 1.0
 * 
*/

#include "BME680reg.h"

/**
 * @brief open connection to BME680
 * @param CLK clock pin
 * @param DTA data pin
 * @return ID chip id
 */
unsigned char BME680_init(unsigned char CLK, unsigned char DTA);

/**
 * @brief reset BME680 device
 * @return results of reset
 */
unsigned char BME680_reset();

/**
 * @brief get chip ID
 * @return ID chip id
 */
unsigned char BME680_getID();
