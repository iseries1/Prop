/**
 * @brief Library for EM7180 sensor fusion hub
 * @author Michael Burmeister
 * @date January 25, 2019
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "em7180.h"


#define EMCLK 1
#define EMSDA 0

int i;
serial *s;

short v[4];
float Q[4];
float A12, A22, A31, A32, A33;
float Yaw, Pitch, Roll;


int main()
{

  i = Em7180_open(EMCLK, EMSDA);
 
  s = simpleterm_pointer();
  
  printi("Value: %x\n", i);
  
  i = Em7180_sensors();
  printi("Sensors: %x\n", i);
  
  i = Em7180_status();
  print("Status: %x\n", i);
  
  Em7180_loadfw();
  
  Em7180_setupdefault();
  
  while(1)
  {
    i = Em7180_status();
//    putStr("Value: ");
//    putHexLen(i, 8);
//    putChar('\n');
    if ((i & 0x02) != 0)
    {
      i = Em7180_error();
      putStr("EM7180 sensor status = ");
      putDec(i);
      putChar('\n');
      if ((i & 0x11) != 0)
        putStr("Magnetometer failure.\n");
      if ((i & 0x12) != 0)
        putStr("Accelerometer failure.\n");
      if ((i & 0x14) != 0)
        putStr("Gyro failure.\n");
      if ((i & 0x21) != 0)
        putStr("Magnetometer initialization failure.\n");
      if ((i & 0x22) != 0)
        putStr("Accelerometer initialization failure.\n");
      if ((i & 0x24) != 0)
        putStr("Gyro initialization failure.\n");
      if ((i & 0x30) != 0)
        putStr("Math error.\n");
      if ((i & 0x80) != 0)
        putStr("Invalid sample rate.\n");
      i = 0;
    }
    
    if ((i & 0x10) == 0x10)
    {
      Em7180_readaccelerometer(v);
//      printi("Accel: %d, %d, %d\n", v[0], v[1], v[2]);
    }
    
    if ((i & 0x20) == 0x20)
    {
      Em7180_readgyro(v);
//      printi("Gyro: %d, %d, %d\n", v[0], v[1], v[2]);
    }
    
    if ((i & 0x08) == 0x08)
    {
      Em7180_readmagnetometer(v);
//      printi("Mag: %d, %d, %d\n", v[0], v[1], v[2]);
    }
    
    if ((i & 0x04) == 0x04)
    {
      Em7180_readquaternions(Q);
//      print("Quat: %f, %f, %f, %f\n", Q[0], Q[1], Q[2], Q[3]);
//      print("%f %f %f %f\n", Q[0], Q[1], Q[2], Q[3]);
      A12 =   2.0f * (Q[1] * Q[2] + Q[0] * Q[3]);
      A22 =   Q[0] * Q[0] + Q[1] * Q[1] - Q[2] * Q[2] - Q[3] * Q[3];
      A31 =   2.0f * (Q[0] * Q[1] + Q[2] * Q[3]);
      A32 =   2.0f * (Q[1] * Q[3] - Q[0] * Q[2]);
      A33 =   Q[0] * Q[0] - Q[1] * Q[1] - Q[2] * Q[2] + Q[3] * Q[3];
      Pitch = -asinf(A32);
      Roll  = atan2f(A31, A33);
      Yaw   = atan2f(A12, A22);
      Pitch *= 180.0f / PI;
      Yaw   *= 180.0f / PI;
      if (Yaw < 0) Yaw   += 360.0f ;
      Roll  *= 180.0f / PI;
      print("%3.0f %3.0f %3.0f\n", Yaw, Pitch, Roll);
    }
    
    pause(250);
    
  }  
}
