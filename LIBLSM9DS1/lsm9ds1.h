/**
 * @file lsm9ds1.h
 * @brief Sparkfun 9DOF board Read Accel and Gyro data
 * @author Michael Burmeister
 * @date August 29, 2017
 * @version 1.0
 * @mainpage Custom Libraries
 * <a href="lsm9ds1_8h.html">LSM9DS1 Parallax IMU Driver.</a><br>
 */

#define LSM9DS1Address 0x6a
#define LSM9DS1Secondary 0x6b
#define LSM9DS1MagAddress 0x1c
#define LSM9DS1MagSecondary 0x1e

/**
 * @brief open connection to IMU
 * @param SCL clock pin
 * @param SDA data pin
 * @return signature of IMU 0x68
 */
unsigned char LSMInit(short SCL, short SDA);

/**
 * @brief get accelerometer/gyro signature
 * @return signature of IMU 0x68
 */
unsigned char AccelGyroSignature();

/**
 * @brief accelerometer or gyro ready 1, 2 or 4
 * @return status 1 - accel, 2 - gyro, 4 - temperature
 */
unsigned char AccelGyroReady();

/**
 * @brief magnetometer ready
 * @return 0 - not ready
 */
unsigned char MagReady();

/**
 * @brief read accelerometer values
 * @param x axes
 * @param y axes
 * @param z axes
 */
void readAccel(short *x, short *y, short *z);

/**
 * @brief read gyro values
 * @param x axes
 * @param y axes
 * @param z axes
 */
void readGyro(short *x, short *y, short *z);

/**
 * @brief read magnetometer values
 * @param x - axes
 * @param y - axes
 * @param z - axes
 */
void readMag(short *x, short *y, short *z);

/**
 * @brief read magnetometer signature
 * @return signature 0x3d
 */
unsigned char MagSignature();

/**
 * @brief set accelerometer range
 * @param range 0 - 2g, 1 - 16g, 2 - 4g, 3 - 8g
 */
void setAccelRange(unsigned char range);

/**
 * @brief set gyro range
 * @param range 0 - 245, 1 - 500, 2 - N/A, 3 - 2000 dps
 */
void setGyroRange(unsigned char range);

/**
 * @brief set magnetometer range
 * @param range 0 - 4guass, 1 - 8guass, 2 - 12guass, 3 - 16guass
 */
void setMagRange(unsigned char range);

/**
 * @brief set accelerometer rate
 * @param rate 0 - power down, 1 - 10hz, 2 - 50hz, 3 - 119hz, 4 - 238hz, 5 - 476hz, 6 - 952hz, 7 - N/A
 */
void setAccelRate(unsigned char rate);

/**
 * @brief set gyro rate
 * @param rate 0 - power down, 1 - 14.9hz, 2 - 59.5hz, 3 - 119hz, 4 - 238hz, 5 - 476hz, 6 - 952hz, 7 - N/A
 */
void setGyroRate(unsigned char rate);

/**
 * @brief set gyro band width
 * @param bandwidth 0 - default, 1, 2, 3
 */
void setGyroBW(unsigned char bandwidth);

/**
 * @brief set magnetometer rate
 * @param rate 0 - .625hz, 1 - 1.25hz, 2 - 2.5hz, 3 - 5hz, 4 - 10hz, 5 - 20hz, 6 - 40hz, 7 - 80hz
 */
void setMagRate(unsigned char rate);

/**
 * @brief get temperature
 * @return temperature in celsius
 */
short getTemperature();

/**
 * @brief set orientation of unit
 * @param orientation 0 - default, 4 - z+, 5 - y+, 6 - x+
 */
void setOrientation(unsigned char orientation);

/**
 * @brief set accelerometer offset
 * @param x axes
 * @param y axes
 * @param z axes
 */
void setAccelOffset(short x, short y , short z);

/**
 * @brief set gyro offset
 * @param x axes
 * @param y axes
 * @param z axes
 */
void setGyroOffset(short x, short y, short z);

/**
 * @brief get accelerometer rate
 * @return rate
 */
unsigned char getAccelRate();

/**
 * @brief get gyro rate
 * @return rate
 */
unsigned char getGyroRate();

/**
 * @brief get gyro offsets
 * @param x axes
 * @param y axes
 * @param z axes
 */
void getGyroOffset(short *x, short *y, short *z);

