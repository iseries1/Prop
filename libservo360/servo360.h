/**
 * @file servo360.h
 * @brief Drive Servo 360 
 * @author Michael Burmeister
 * @date January 20, 2018
 * @version 1.0
*/

#include "servo.h"
#include "timer.h"

/**
 * @details Startup Servo Angle Process
 * 
 * @return Cog number
 */
void S360_start(void);

/**
 * @details Add a Servo 
 * @param s Servo pin
 * @param f Servo feedback pin
 * 
*/
void S360_add(short s, short f);

/**
 * @details Remove a Servo
 * @param s Servo pin
 * @param f Servo feedback pin
 * 
*/
void S360_remove(short s, short f);

/**
 * @details Set Servo Angle
 * @param s Servo pin
 * @param a Servo angle
 * 
*/
void S360_setAngle(short s, short a);

/**
 * @details Get Servo Angle
 * @param s Servo pin
 * @return Servo angle
 * 
*/
short S360_getAngle(short s);

/**
 * @details get number of revolutions
 * @return long value of count
 */
long S360_getCount(void);
