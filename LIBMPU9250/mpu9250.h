/**
 * @file mpu9250.h
 * @brief 9Dof senser
 * @author Michael Burmeister
 * @date December 19, 2016
 * @version 1.0
 * 
 */
#include "mpu9250Reg.h"

//#ifdef _MPU9250_H
//#define _MPU9250_H

/**
 * @brief Read the accelerometer values
 * @param x pointer to x
 * @param y pointer to y
 * @param z pointer to z
 */
  void readAccelData(int16_t *x, int16_t *y, int16_t *z);
  
/**
 * @brief Read Gyro reading
 * @param x pointer to x
 * @param y pointer to y
 * @param z pointer to z
 */
  void readGyroData(int16_t *x, int16_t *y, int16_t *z);
  
/**
 * @brief Read Magnetometer reading
 * @param x pointer to x
 * @param y pointer to y
 * @param z pointer to z
 */
  void readMagData(int16_t *x, int16_t *y, int16_t *z);
  
/**
 * @brief Get temperature
 * 
 * @return temp
 */
  int16_t readTempData();

 /**
 * @brief Set Accelerometer range
 * 00 - 2g
 * 01 - 4g
 * 02 - 8g
 * 03 - 16g
 * @param range
 */
  void setAccelRange(uint8_t range);
  
 /**
 * @brief Set Accelerometer rate
 *  enable low pass filter
 * @param rate
 */
  void setAccelRate(uint8_t rate);
  
 /**
 * @brief Get Accelerometer range
 *
 * @return range
 */
  uint8_t getAccelRange(void);
  
 /**
 * @brief Get Accelerometer bias
 * @param x pointer to x
 * @param y pointer to y
 * @param z pointer to z
 */
  void getAccelBias(int16_t *x, int16_t *y, int16_t *z);

 /**
 * @brief Set Accelerometer bias
 * @param x pointer to x
 * @param y pointer to y
 * @param z pointer to z
 */
  void setAccelBias(int16_t x, int16_t y, int16_t z);

 /**
 * @brief Set Gyro range
 * @brief 00 - 250dps
 * @brief 01 - 500dps
 * @brief 02 - 1000dps
 * @brief 03 - 2000dps
 * 
 */
  void setGyroRange(uint8_t);

 /**
 * @brief Get Gyro range
 *
 * @return range
 */
  uint8_t getGyroRange(void);
  
 /**
 * @brief Get Gyro bias
 * @param x pointer to x
 * @param y pointer to y
 * @param z pointer to z
 */
  void getGyroBias(int16_t *x, int16_t *y, int16_t *z);
  
 /**
 * @brief Set Gyro bias
 * @param x bias value
 * @param y bias value
 * @param z bias value
 */
  void setGyroBias(int16_t x, int16_t y, int16_t z);
  
 /**
 * @brief Set Sample Rate
 * @param rate
 */
  void setSampleRate(uint8_t rate);
  
 /**
 * @brief get Sample Rate
 *
 */
  uint8_t getSampleRate(void);
  
/**
 * @brief Initialize AK8964 unit
 * @param x pointer to x value
 * @param y pointer to y value
 * @param z pointer to z value
 */
  void initMag(uint8_t *x, uint8_t *y, uint8_t *z);

 /**
 * @brief Set Magnetometer range
 * 00 - Power Down
 * 01 - Single Measurement
 * 02 - Continues Measurement Mode 1 8hz
 * 06 - Continues Messurement Mode 2 100hz
 * 04 - External Triger Mode
 * 08 - Self Test Mode
 * @param range
 */
  void setMagRange(uint8_t range);
  
/**
 * @brief Initialize MPU9250 unit
 * 
 */
  void initMPU9250();
  
  
/**
 * @brief Who Am I value
 * 
 * @return whoami value 0x71
 */
  uint8_t WhoAmIMPU9250(void);
  
/**
 * @brief Who Am I value Magnetometer
 * 
 * @return whoami value 0x48
 */
  uint8_t WhoAmIMag(void);
  
/**
 * @brief Get interupt state
 * 
 * @return whoami value 0x48
 */
  uint8_t getIntStatus(void);
  
/**
 * @brief Open connection to MPU9250 device
 * 
 * @param SCL i2c clock pin
 * @param SDA i2c data pin
 */
  uint8_t openMPU9250(int SCL, int SDA);

/**
 * @brief Set Interrupt enable pin
 * 1 - enable, 0 - disable
 * @param enable
 * 
 */
  void setInterrupt(uint8_t enable);

/**
 * @brief Hardware reset
 * 
 */
  void reset(void);

/**
 * @brief set Power
 * 
 * @param power1 
 * @param power2
 * 
 */
  void Power(uint8_t power1, uint8_t power2);

/**
 * @brief set Fifo mode
 * 
 * @param Fifo 
 * 
 */
  void setFifo(uint8_t Fifo);

/**
 * @brief get Fifo count
 * 
 * @return count 
 * 
 */
  uint16_t getFifoCount(void);

/**
 * @brief set I2C Master
 * 
 * @param master 
 * 
 */
  void setI2CMaster(uint8_t master);

/**
 * @brief set UsrCtl
 * 
 * @param control 
 * 
 */
  void setUsrCtl(uint8_t control);

/**
 * @brief set Configuration
 * 
 * @param config 
 * 
 */
  void setConfig(uint8_t config);

/**
 * @brief read Fifo data
 * 
 * @param count 
 * @param *data 
 * 
 */
  void readFifo(uint16_t count, uint8_t *data);

