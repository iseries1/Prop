/**
 * @file windspd.h
 * @brief Determine the wind speed 
 * @author Michael Burmeister
 * @date January 27, 2016
 * @version 1.1
 * 
*/

#ifndef WINDSPD_H
#define WINDSPD_H

/**
 * @brief Start Wind Speed Monitor
 *
 * @param hall Pin connect to hall output
 * @return Cog number of wind monitor
*/
int windspd_open(int hall);

/**
 * @brief Get current wind speed
 *
 * @return MPH wind speed
*/
int windspd_speed(void);

/**
 * @brief Stop wind monitor
 *
 * @return Nothing
*/
void windspd_close(void);

#endif
