/**
 * @brief MPU9250 Sparkfun IMU board
 * @author Michael Burmeister
 * @date December 19, 2016
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "mpu9250.h"

#define SCL 13
#define SDA 14

  int16_t gyroCount[3];   // Stores the 16-bit signed gyro sensor output
  int16_t magCount[3];    // Stores the 16-bit signed magnetometer sensor output

  // Variables to hold latest sensor data values
  int16_t ax, ay, az, gx, gy, gz, mx, my, mz;
  int8_t mcx, mcy, mcz;
 
  // Bias corrections for gyro and accelerometer
  int gyroBias[3] = {0, 0, 0};
  int accelBias[3] = {0, 0, 0};
  float SelfTest[6];

unsigned int pp;
unsigned int nt;

int main()
{
  uint8_t i, j;
  i = openMPU9250(SCL, SDA);

  print("MPU signature(0x71): %x\n", i);

  getAccelBias(&ax, &ay, &az);
  print("Accel Bias: %d, %d, %d\n", ax, ay, az);
//  setAccelBias(14, 7, -13);
  
  getGyroBias(&gx, &gy, &gz);
  print("Gyro Bias: %d, %d, %d\n", gx, gy, gz);
  
  getAccelBias(&ax, &ay, &az);
  print("Accel Bias: %d, %d, %d\n", ax, ay, az);

  initMPU9250();

  j = WhoAmIMag();
  
  print("Mag signature(0x48): %x\n", j);
  
  initMag(&mcx, &mcy, &mcz);
  print("Mag Calibration: %d, %d, %d\n", mcx, mcy, mcz);

  print("Ax, Ay, Az, Gx, Gy, Gz\n");
  nt = 0;
  pp = CNT;
  while(1)
  {
    // If intPin goes high, all data registers have new data
    // On interrupt, check if data ready interrupt
    if (getIntStatus())
    {
      readAccelData(&ax, &ay, &az);  // Read the x/y/z adc values
      readGyroData(&gx, &gy, &gz);  // Read the x/y/z adc values
      readMagData(&mx, &my, &mz);  // Read the x/y/z adc values
    }

    if (nt + 20000000 < CNT)   //250 milliseconds
    {
      print("%d, %d, %d, ", ax, ay, az);
      print("%d, %d, %d\n", gx, gy, gz);
      nt = CNT;
    }      
  }
}
