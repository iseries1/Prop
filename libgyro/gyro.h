/**
 * @file gyro.h
 * @brief Using Gyroscope module L3G4200D
 * @author Michael Burmeister
 * @date January 5, 2014
 * @version 1.0
 */

#ifndef GYRO_H
#define GYRO_H

#include "simpletools.h"
#include "simplei2c.h"

/**
 * @details Open Gyro Connection
 * 
 * @param SCL i2c Clock pin
 * @param SDA i2c Data pin
 * @return cog number
 */
int Gyro_Open(int SCL, int SDA);

/**
 * @details Get the Gyro Reading
 * 
 * @param x X pointer to average x value
 * @param y Y pointer to average y value
 * @param z Z pointer to average z value
 */
void Gyro_ReadXYZ(int *x, int *y, int *z);

/**
 * @details Check Gyro Status
 * 
 * @return status
 */
int Gyro_Status(void);

/**
 * @details Shutdown Gyro Connection
 */
void Gyro_Close(void);

#endif
