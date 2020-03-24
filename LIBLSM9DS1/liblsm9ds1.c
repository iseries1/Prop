/**
 * @brief LSM9DS1 Sparkfun IMU board
 * @author Michael Burmeister
 * @date August 31, 2017
 * @version 1.0
 * 
*/


/**
 * Table 3 values:
 *   2g = .061mg, 4g = .122mg, 8g = .244mg, 16g = .732mg
 *   2g = 16393, 4g = 8197, 8g = 4098, 16g = 1366
 *   
 *   245dps = 8.75mdps, 500dsp = 17.5mdps, 2000dps = 70mdps
 *   245dps = 114, 500dsp = 571, 2000dps = 14
 *
*/

#include "simpletools.h"
#include "lsm9ds1.h"

#define SCL 1
#define SDA 0

int _getDelay(long *);

short ax, ay, az;
short gx, gy, gz;
long tax, tay, taz;
long tgx, tgy, tgz;
short Temp;
long tm, _PCNT;
int Prt, Ang;


int main()
{
  int i;
  int Total;
  int Gyro;
  int Accel;
  
  i = LSMInit(SCL, SDA);
  print("Signature: %x\n", i);
  setGyroRange(0x00);
  setAccelRange(0x00);
  i = AccelGyroReady();
  print("Ready: %x\n", i);
  setAccelRange(0);
  setGyroRange(1);
  setMagRange(0);
  setMagRate(1);
  setAccelRate(3);
  setGyroRate(3);
  setGyroBW(0);
  setAccelOffset(209, 45, -484);
  getGyroOffset(&gx, &gy, &gz);
  
  print("%d, %d, %d\n", gx, gy, gz);

  setGyroOffset(gx, gy, gz);
  i = getAccelRate();
  print("Accel: %x\n", i);
  print("Time, Ax, Ay, Az, Gx, Gy, Gz\n");
  readAccel(&ax, &ay, &az);
  readGyro(&gx, &gy, &gz);
  tax = 0;
  tay = 0;
  taz = 0;
  tgx = 0;
  tgy = 0;
  tgz = 0;
  
  Prt = 0;
  Ang = 0;
  
  Total = 0;
  Gyro = 0;
  Accel = 0;
  
  pause(1000);
  readAccel(&ax, &ay, &az);
  readGyro(&gx, &gy, &gz);
  _getDelay(&_PCNT);
  
  while (1)
  {
    tm = _getDelay(&_PCNT);
    Prt += tm;
    Ang += tm;
    
    i = AccelGyroReady();
    if ((i & 0x01) == 1)
    {
      readAccel(&ax, &ay, &az);
      tax += ax;
      tay += ay;
      taz += az;
      Accel++;
      Total++;
    }      
    if ((i & 0x02) == 2)
    {
      readGyro(&gx, &gy, &gz);
      tgx += gx;
      tgy += gy;
      tgz += gz;
      Gyro++;
    }
    if ((i & 0x04) == 4)
      Temp = getTemperature();
    
    if (Total > 255)
    {
      print("\n %d, %d, %d, %d, %d, %d, %d\n", Ang/1000, tax, tay, taz, tgx, tgy, tgz);
      ax = tax / Accel;
      ay = tay / Accel;
      az = taz / Accel;
      if (az > 0)
        az = az - 16393;
      else
        az = az + 16393;
        
      gx = tgx / Gyro;
      gy = tgy / Gyro;
      gz = tgz / Gyro;
      print("\n %d, %d, %d, %d, %d, %d, %d\n", Prt/1000, ax, ay, az, gx, gy, gz);
      print("Total Accel: %d, Gyro: %d \n", Accel, Gyro);
      
      while(1);
    }      
  }
}

int _getDelay(long *D)
{
  long t;
  
  t = CNT - *D;
  *D = CNT;
  if (t < 0)
    t = UINT32_MAX + t;

  return (int)t/us;
}

      