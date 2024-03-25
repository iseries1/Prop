/**
 * @file icm20948.h
 * @brief ICM20948 9Dof sensor driver
 * @author Michael Burmeister
 * @date February 20, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initialize device driver
 * @param icmclk clock pin
 * @param icmdta data pin
 * @return 0 - found device
 */
int ICM20948_Init(int icmclk, int icmdta);

/**
 * @brief Set Mode of Operation
 * @param mode 
 * 0 - Stream
 * 1 - One Shot
 */
void ICM20948_FifoMode(int mode);

/**
 * @brief Enable DMP
 * @param enable 0 - off, 1 - on
 */
void ICM20948_DMP(int enable);

/**
 * @brief Enable FIFO
 * @param enable 0 - off, 1 - on
 */
void ICM20948_FIFO(int enable);

/**
 * @brief Set Fifo Data
 * @param data
 * 1 -> Temperature,
 * 2 -> GyroX, 
 * 4 -> GyroY,
 * 8 -> GyroZ, 
 * 16 -> Accelerometer
 * 256 -> Slave 0
 * 512 -> Slave 1
 * 1024 -> Slave 2
 * 2048 -> Slave 3
*/
void ICM20948_SetFifoData(int data);

/**
 * @brief Fifo Count
 * @return count
*/
short ICM20948_FifoCount(void);

/**
 * @brief Read Fifo Data
 * @param count of data to read
 * @param buffer to hold data
 * @return number of bytes read
 * remember data is two bytes
*/
short ICM20948_ReadFifo(int count, char *buffer);

/**
 * @brief Enable I2C Master
 * @param enable 0 - off, 1 - on
 */
void ICM20948_I2CMaster(int enable);

/**
 * @brief Reset Unit
 */
void ICM20948_Reset(void);

/**
 * @brief Sleep Mode
 * @param mode 0 - Sleep Mode off, 1 - On
 */
void ICM20948_Sleep(int mode);

/**
 * @brief Enable Low Power Mode
 * @param mode 0 - Disable Low Power, 1 - Enable Low Power
 */
void ICM20948_EnableLowPower(int mode);

/**
 * @brief Set Clock Source
 * @param source 0 - 20Mhz, 1-5 Internal, 6 - 20Mhz, 7 - Stop Clock
 */
void ICM20948_SetClock(int source);

/**
 * @brief Interupt Status
 * @return status
 * b0 - Master
 * b1 - DMP
 * b2 - PLL
 * b3 - Motion
 */
int ICM20948_Interupts(void);

/**
 * @brief Set Bypass Mode
 * @param mode 0 - off 1 - on
 */
void ICM20948_ByPass(int mode);

/**
 * @brief Get Delay Time
 * @return delay
 */
int ICM20948_Delay(void);

/**
 * @brief Get Data Ready
 * @return ready 0 - No, 1 - 3 data
*/
int ICM20948_DataReady(void);

/**
 * @brief Get Accel Values
 * @param x - *x
 * @param y - *y
 * @param z - *z
 */
void ICM20948_Accel(short *x, short *y, short *z);

/**
 * @brief Get Gyro Values
 * @param x - *x
 * @param y - *y
 * @param z - *z
 */
void ICM20948_Gyro(short *x, short *y, short *z);

/**
 * @brief Get Temperature
 * @return temp in celsius
 */
int ICM20948_Temp(void);

/**
 * @brief Reset FIFO
 */
void ICM20948_ResetFifo(void);

/**
 * @brief Config Gyro
 * @param filter 0 - 7
 * @param range 0 - 250dps, 1 - 500dps, 2 - 1000dps, 3 - 2000dps
 * @param enable filter
 */
void ICM20948_ConfigGyro(int filter, int range, int enable);

/**
 * @brief Gyro Offsets
 * @param x - address to short
 * @param y - address to short
 * @param z - address to short
*/
void ICM20948_GyroOffsets(short *x, short *y, short *z);

/**
 * @brief Set Gyro Offsets
 * @param x value
 * @param y value
 * @param z value
*/
void ICM20948_SetGyroOffsets(short x, short y, short z);

/**
 * @brief Config Accelerometer
 * @param filter 0 - 7
 * @param range 0 - 2g, 1 - 4g, 2 - 8g, 3 - 16g
 * @param enable filter
 */
void ICM20948_ConfigAccel(int filter, int range, int enable);

/**
 * @brief Accelerometer Offsets
 * @param x - address to short
 * @param y - address to short
 * @param z - address to short
*/
void ICM20948_AccelOffsets(short *x, short *y, short *z);

/**
 * @brief Set Accelerometer Offsets
 * @param x
 * @param y
 * @param z
*/
void ICM20948_SetAccelOffsets(short x, short y, short z);

/**
 * @brief Get Mag Who Am I
 * @return value 0x09
 */
int ICM20948_MagWhoAmI(void);

/**
 * @brief Get Mag values
 * @param x - *x
 * @param y - *y
 * @param z - *z
 * @return status data overflow
 */
int ICM20948_Mag(short *x, short *y, short *z);

/**
 * @brief Get Mag Control
 * @return mode
 * 0 - Power Down
 * 1 - Single Measure
 * 2 - Continuous mode 1
 * 4 - Continuous mode 2
 * 6 - Continuous mode 3
 * 8 - Continuous mode 4
 * 16 - Self Test
 */
int ICM20948_MagCtrl(void);

/**
 * @brief Set Mag Mode
 * @param mode
 * 0 - Power Down
 * 1 - Single Measure
 * 2 - Continuous mode 1
 * 4 - Continuous mode 2
 * 6 - Continuous mode 3
 * 8 - Continuous mode 4
 * 16 - Self Test
 */
void ICM20948_MagMode(int mode);

/**
 * @brief Set Memory Bank
 * @param bank 0 - 4
 */
void ICM20948_SetBank(int bank);

/**
 * @brief Write Memory Data
 * @param addr - starting address 0x00 - 0xff
 * @param data - 16 bytes of data
 */
void ICM20948_WriteMemory(short addr, char *data);

/**
 * @brief Read Memory Data
 * @param addr - address to start reading 0x00 - 0xff
 * @param data - array of 16 bytes of data
 */
void ICM20948_ReadMemory(short addr, char *data);
