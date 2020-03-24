/*
 * @file mpu9250.c
 * @brief Sparkfun MPU9250 9Dof board
 * @author Michael Burmeister
 * @date December 19, 2016
 * @version 1.1
 * 
 */

#include "simpletools.h"
#include "mpu9250.h"

void writeByte(uint8_t , uint8_t , uint8_t );
uint8_t readByte(uint8_t , uint8_t);
void readBytes(uint8_t , uint8_t , uint8_t , uint8_t *);

i2c *mpu;

    
void readAccelData(int16_t* ax, int16_t* ay, int16_t* az)
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  readBytes(MPU9250_ADDRESS, ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
  *ax = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  *ay = ((int16_t)rawData[2] << 8) | rawData[3] ;  
  *az = ((int16_t)rawData[4] << 8) | rawData[5] ; 
}       

void readGyroData(int16_t* gx, int16_t* gy, int16_t* gz)
{
  uint8_t rawData[6];  // x/y/z gyro register data stored here
  readBytes(MPU9250_ADDRESS, GYRO_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers sequentially into data array
  *gx = ((int16_t)rawData[0] << 8) | rawData[1] ;  // Turn the MSB and LSB into a signed 16-bit value
  *gy = ((int16_t)rawData[2] << 8) | rawData[3] ;  
  *gz = ((int16_t)rawData[4] << 8) | rawData[5] ; 
}

void readMagData(int16_t* mx, int16_t* my, int16_t* mz)
{
  // x/y/z magnetometer register data, ST2 register stored here, must read ST2 at end of
  // data acquisition
  uint8_t rawData[7];
  // Wait for magnetometer data ready bit to be set
  if(readByte(AK8963_ADDRESS, AK8963_ST1) & 0x01)
  {
    // Read the six raw data and ST2 registers sequentially into data array
    readBytes(AK8963_ADDRESS, AK8963_XOUT_L, 7, &rawData[0]);
    uint8_t c = rawData[6]; // End data read by reading ST2 register
    // Check if magnetic sensor overflow set, if not then report data
    if(!(c & 0x08))
    {
      // Turn the MSB and LSB into a signed 16-bit value
      *mx = ((int16_t)rawData[1] << 8) | rawData[0]; // Data stored as little Endian 
      *my = ((int16_t)rawData[3] << 8) | rawData[2];
      *mz = ((int16_t)rawData[5] << 8) | rawData[4];
    }
  }
}

int16_t readTempData()
{
  uint8_t rawData[2];  // x/y/z gyro register data stored here
  readBytes(MPU9250_ADDRESS, TEMP_OUT_H, 2, &rawData[0]);  // Read the two raw data registers sequentially into data array 
  return ((int16_t)rawData[0] << 8) | rawData[1];  // Turn the MSB and LSB into a 16-bit value
}

void setAccelRange(uint8_t range)
{
  range = range << 3;
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG, range);
}

uint8_t getAccelRange(void)
{
  uint8_t range = readByte(MPU9250_ADDRESS, ACCEL_CONFIG);
  range = range >> 3;
  return range;
}

void setAccelRate(uint8_t rate)
{
//  rate = rate | 0x10;
  writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, rate);
}

void setAccelBias(int16_t x, int16_t y, int16_t z)
{
  uint8_t rawData[6];
  
  rawData[0] = (x >> 8) & 0xff;
  rawData[1] = x & 0xfe;
  rawData[2] = (y >> 8) & 0xff;
  rawData[3] = y & 0xfe;
  rawData[4] = (z >> 8) & 0xff;
  rawData[5] = z & 0xfe;
  writeByte(MPU9250_ADDRESS, XA_OFFSET_H, rawData[0]);
  writeByte(MPU9250_ADDRESS, XA_OFFSET_L, rawData[1]);
  writeByte(MPU9250_ADDRESS, YA_OFFSET_H, rawData[2]);
  writeByte(MPU9250_ADDRESS, YA_OFFSET_L, rawData[3]);
  writeByte(MPU9250_ADDRESS, ZA_OFFSET_H, rawData[4]);
  writeByte(MPU9250_ADDRESS, ZA_OFFSET_L, rawData[5]);
}

void getAccelBias(int16_t *x, int16_t *y, int16_t *z)
{
  uint8_t rawData[6];
  
  readBytes(MPU9250_ADDRESS, XA_OFFSET_H, 2, &rawData[0]);
  readBytes(MPU9250_ADDRESS, YA_OFFSET_H, 2, &rawData[2]);
  readBytes(MPU9250_ADDRESS, ZA_OFFSET_H, 2, &rawData[4]);
  *x = ((int16_t)rawData[0] << 8) | rawData[1];
  *y = ((int16_t)rawData[2] << 8) | rawData[3];
  *z = ((int16_t)rawData[4] << 8) | rawData[5];
}
  
void setGyroRange(uint8_t range)
{
  range = range << 3;
  writeByte(MPU9250_ADDRESS, GYRO_CONFIG, range);
}

uint8_t getGyroRange(void)
{
  uint8_t range = readByte(MPU9250_ADDRESS, GYRO_CONFIG);
  range = range >> 3;
  return range;
}

void getGyroBias(int16_t *x, int16_t *y, int16_t *z)
{
  uint8_t rawData[6];
  
  readBytes(MPU9250_ADDRESS, XG_OFFSET_H, 6, rawData);
  *x = ((int16_t)rawData[0] << 8) | rawData[1];
  *y = ((int16_t)rawData[2] << 8) | rawData[3];
  *z - ((int16_t)rawData[4] << 8) | rawData[5];
}

void setGyroBias(int16_t x, int16_t y, int16_t z)
{
  uint8_t rawData[6];
  
  rawData[0] = (x >> 8) & 0xFF;
  rawData[1] = x & 0xFF;
  rawData[2] = (y >> 8) & 0xFF;
  rawData[3] = y & 0xFF;
  rawData[4] = (z >> 8) & 0xFF;
  rawData[5] = z & 0xFF;
  writeByte(MPU9250_ADDRESS, XG_OFFSET_H, rawData[0]);
  writeByte(MPU9250_ADDRESS, XG_OFFSET_L, rawData[1]);
  writeByte(MPU9250_ADDRESS, YG_OFFSET_H, rawData[2]);
  writeByte(MPU9250_ADDRESS, YG_OFFSET_L, rawData[3]);
  writeByte(MPU9250_ADDRESS, ZG_OFFSET_H, rawData[4]);
  writeByte(MPU9250_ADDRESS, ZG_OFFSET_L, rawData[5]);
}

void setSampleRate(uint8_t rate)
{
  writeByte(MPU9250_ADDRESS, SMPLRT_DIV, rate);
}

uint8_t getSampleRate()
{
  uint8_t rate;
  
  rate = readByte(MPU9250_ADDRESS, SMPLRT_DIV);
  return rate;
}

void setMagRange(uint8_t range)
{
  writeByte(MPU9250_ADDRESS, AK8963_CNTL, 0x00);
  pause(10);
  writeByte(MPU9250_ADDRESS, AK8963_CNTL, range);
  pause(10);
}
  
void initMag(uint8_t* mx, uint8_t* my, uint8_t* mz)
{
  // First extract the factory calibration for each magnetometer axis
  uint8_t rawData[3];  // x/y/z magnetometer calibration data stored here
  setMagRange(0x0F); // Enter Fuse ROM access mode
  readBytes(AK8963_ADDRESS, AK8963_ASAX, 3, &rawData[0]);  // Read the x-, y-, and z-axis calibration values
  *mx =  rawData[0];   // Return x-axis sensitivity adjustment values, etc.
  *my =  rawData[1];  
  *mz =  rawData[2];
  // Configure the magnetometer for continuous read and highest resolution
  // set Mscale bit 4 to 1 (0) to enable 16 (14) bit resolution in CNTL register,
  // and enable continuous mode data acquisition Mmode (bits [3:0]), 0010 for 8 Hz and 0110 for 100 Hz sample rates
  setMagRange(0x02); // Set magnetometer data resolution and sample ODR
}

void initMPU9250()
{  
 // wake up device
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors 
  pause(100); // Wait for all registers to reset 

 // get stable time source
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);  // Auto select clock source to be PLL gyroscope reference if ready else
  pause(200); 
  
 // Configure Gyro and Thermometer
 // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively; 
 // minimum delay time for this setting is 5.9 ms, which means sensor fusion update rates cannot
 // be higher than 1 / 0.0059 = 170 Hz
 // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
 // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
  writeByte(MPU9250_ADDRESS, CONFIG, 0x03);  

 // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
  setSampleRate(0x04);  // Use a 200 Hz rate; a rate consistent with the filter update rate 
                        // determined inset in CONFIG above
 
 // Set gyroscope full scale range
 // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
  setGyroRange(0);
    
 // Set accelerometer full-scale range configuration
  setAccelRange(0);
  
 // Set accelerometer sample rate configuration
 // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
 // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
  setAccelRate(3);
  
 // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates, 
 // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

  // Configure Interrupts and Bypass Enable
  // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
  // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips 
  // can join the I2C bus and all can be controlled by the Arduino as master
  setInterrupt(1);
   pause(100);
}


uint8_t WhoAmIMPU9250()
{
  uint8_t i;
  i = readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  return i;
}

uint8_t WhoAmIMag()
{
  uint8_t i;
  i = readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
  return i;
}
  
uint8_t getIntStatus()
{
  uint8_t i;
  i = readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01;
  return i;
}
  
uint8_t openMPU9250(int SCL, int SDA)
{
  uint8_t i;
  mpu = i2c_newbus(SCL, SDA, 0);
  i = WhoAmIMPU9250();
  return i;
}

void setInterrupt(uint8_t i)
{
    writeByte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
  if (i == 1)
    writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
  else
    writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x00);  // Disable data ready (bit 0) interrupt
}

void reset(void)
{
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80);
  pause(100);
}

void Power(uint8_t p1, uint8_t p2)
{
  writeByte(MPU9250_ADDRESS, PWR_MGMT_1, p1);
  writeByte(MPU9250_ADDRESS, PWR_MGMT_2, p2);
  pause(100);
}

void setFifo(uint8_t f)
{
  writeByte(MPU9250_ADDRESS, FIFO_EN, f);
}

uint16_t getFifoCount(void)
{
  uint16_t data;
  uint8_t rawData[2];
  
  readBytes(MPU9250_ADDRESS, FIFO_COUNTH, 2, rawData);
  data = ((uint16_t)rawData[0] << 8) | rawData[1];
  return data;
}

void readFifo(uint16_t count, uint8_t *fifo)
{
  readBytes(MPU9250_ADDRESS, FIFO_R_W, count, fifo);
}
  
void setI2CMaster(uint8_t i)
{
  writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, i);
}

void setUsrCtl(uint8_t u)
{
  writeByte(MPU9250_ADDRESS, USER_CTRL, u);
}

void setConfig(uint8_t c)
{
  writeByte(MPU9250_ADDRESS, CONFIG, c);
}

  
// i2c read and write protocols
void writeByte(uint8_t address, uint8_t subAddress, uint8_t data)
{
  i2c_out(mpu, address, subAddress, 1, &data, 1);
}

uint8_t readByte(uint8_t address, uint8_t subAddress)
{
  uint8_t data;
  i2c_in(mpu, address, subAddress, 1, &data, 1);
  return data;
}

void readBytes(uint8_t address, uint8_t subAddress, uint8_t cnt, uint8_t * dest)
{
  i2c_in(mpu, address, subAddress, 1, dest, cnt);
}
