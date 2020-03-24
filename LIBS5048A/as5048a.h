/**
 * @file as5048a.h
 * @brief AS5048 Position Sensor
 * @author Michael Burmeister
 * @date January 19, 2016
 * @version 1.0
 * @mainpage Custom Libraries
 * <a href="as5048a_8h.html">Magnetic Rotary Encoder.</a><br>
*/

#ifndef AS5048A_H
#define AS5048A_H


/**
 * @brief Open connection to as5048a
 *
 * @param CS Chip Select Pin
 * @param SCK SPI Clock Pin
 * @param MOSI Master Out Pin
 * @param MISO Master In Pin
 * @return AS5048a status
*/
int as5048a_open(int CS, int SCK, int MOSI, int MISO);

/**
 * @brief Get current angle from as5048a
 *
 * @return Angle in degrees
*/
int as5048a_readAngle(void);

/**
 * @brief Set offset angle for as5048a
 *
 * @param offset
 * @return Nothing
*/
void as5048a_setOffset(int offset);

#endif
