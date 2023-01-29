/**
 * @file copmotors.h
 * @brief Library for Copter ESC Motor Driver
 * @author Michael Burmeister
 * @date January 23, 2015
 * @version 1.0
 * 
 */

#ifndef copmotors_H
#define copmotors_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "simpletools.h"

/**
 * @details Startup the Motor process
 * 
 * @return Cog number
 */
int Motors_Init(int);

/**
 * @details Shutdown the Motor process
 * 
 */
void Motors_Stop(void);

/**
 * @details Set Motor speed from 1000 to 2000 microseconds
 * 
 * @param Pin Pin number of motor
 * @param Val Speed Value to set from 1000 to 2000 microseconds
 * @return int 0 ok -1 fail
 */
int Motors_Set(int Pin, int Val);

/**
 * @details Set Loop pause amount divided by 8 (40msec / 8 = 5)
 * 
 * @param msec Set the loop pause value between pulses per motor
 */
void Motors_Refresh(int msec);

#endif