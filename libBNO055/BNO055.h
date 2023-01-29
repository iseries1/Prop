/**
 * @file BNO055.h
 * @brief BOSCH BNO055 driver library
 * @author Michael Burmeister
 * @date March 14, 2020
 * @version 1.0
 * 
*/

enum bno055mode
{
  CONFIGMODE = 0,
  ACCONLY = 1,
  MAGONLY = 2,
  GYROONLY = 3,
  ACCMAG = 4,
  ACCGYRO = 5,
  MAGGYRO = 6,
  AMG = 7,
  IMU = 8,
  COMPASS = 9,
  M4G = 10,
  NDOFFMCOFF = 11,
  NDOF = 12
};


/**
 * @brief initalize BNO055 device
 * @param sda i2c data line pin
 * @param scl i2c clock line pin
 * @return chip id
 */
int BNO055_init(int sda, int scl);

/**
 * @brief get chip id
 * @return chip id 0xA0
 */
int BNO055_ID(void);

/**
 * @brief get accelerometer id
 * @return id 0xFB
 */
int BNO055_ACCID(void);

/**
 * @brief get magnetometer id
 * @return id 0x32
 */
int BNO055_MAGID(void);

/**
 * @brief get gyro id
 * @return id 0x0f
 */
int BNO055_GYROID(void);

/**
 * @brief set operating mode
 * @mode
 */
int BNO055_OperatingMode(unsigned char mode);

/**
 * @brief get operating mode
 * @return mode
 */
int BNO055_getOperatingMode(void);

/**
 * @brief get EULER angles
 * @param heading
 * @param roll
 * @param pitch
 * @return status
 */
int BNO055_getEulerAngle(short *heading, short *roll, short *pitch);

/**
 * @brief get temperature
 * @return temperature
 */
int BNO055_Temperature(void);

/**
 * @brief get calibration results
 * @return 0xFF fully calibrated
 */
int BNO055_getCalibration(void);
