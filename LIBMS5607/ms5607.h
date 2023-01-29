/**
 * @file ms5607.h
 * @brief MS5607 pressure drive
 * @author Michael Burmeister
 * @date May 24, 2020
 * @version 1.0
 * 
*/

#define RSLT_256 0x00
#define RSLT_512 0x02
#define RSLT_1024 0x04
#define RSLT_2048 0x06
#define RSLT_4096 0x08

/**
 * @brief initialize MS5607 driver
 * @param scl clock pin
 * @param sda data pin
 * @param osr over sample rate value (RSLT_256, RSLT_512, RSLT_1024, RSLT_2048, RSLT_4096)
 * @return 1 check sum or zero if not found
 */
int ms5607_init(int scl, int sda, int osr);

/**
 * @brief disconnect driver
 */
void ms5607_close(void);

/**
 * @brief get raw temperature
 * @return temperature
 */
int ms5607_rawtemperature(void);

/**
 * @brief get raw air pressure in millibars
 * @return pressure
 */
int ms5607_rawpressure(void);

/**
 * @brief get temperature in celcius
 * @return temperature * 100
 */
int ms5607_temperature(void);

/**
 * @brief get temperature in fahrenheit
 * @return temperature * 100
 */
int ms5607_fahrenheit(void);

/**
 * @brief get pressure in millibars
 * @return pressure
 */
int ms5607_pressure(void);

/**
 * @brief get pressure in millimeters of mercury
 * @return mercury
 */
int ms5607_mercury(void);
