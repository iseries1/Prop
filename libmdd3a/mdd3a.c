/**
 * @brief Dual Channel Motor Driver
 * @author Michael Burmeister
 * @date February 19, 2023
 * @version 1.0
 * 
*/

#include "mdd3a.h"
#include "simpletools.h"

void domdd3a(void *);


int _m1a, _m1b, _m2a, _m2b;
volatile int _M1PWMV;
volatile int _M2PWMV;
volatile int _RUNIT;


void mdd3a_Init(int M1A, int M1B, int M2A, int M2B)
{
  _m1a = M1A;
  _m1b = M1B;
  _m2a = M2A;
  _m2b = M2B;
  
  _M1PWMV = 1500;
  _M2PWMV = 1500;
  
  cog_run(&domdd3a, 40);
}

void mdd3a_SetPWM(int motor1, int motor2)
{
  if (motor1 > 2000)
    motor1 = 2000;
  if (motor1 < 1000)
    motor1 = 1000;
  if (motor2 > 2000)
    motor2 = 2000;
  if (motor2 < 1000)
    motor2 = 1000;
  
  _M1PWMV = motor1;
  _M2PWMV = motor2;
}

void mdd3a_Stop(void)
{
  _RUNIT = 0;
}



/* Run the motors based on PWM value */
void domdd3a(void *par)
{
  long m1, m2;
  unsigned long PCNT;
  
  _RUNIT = 1;
  
  PHSA = 0;
  FRQA = 1;
  CTRA = 0x10000000 | _m1a;
  
  PHSB = 0;
  FRQB = 1;
  CTRB = 0x10000000 | _m2a;

  while (_RUNIT)
  {
    low(_m1a);
    low(_m1b);
    low(_m2a);
    low(_m2b);

    // create dead band and determine direction
    if (_M1PWMV >= 1510)
      CTRA = 0x10000000 | _m1a;

    if (_M1PWMV <= 1490)
      CTRA = 0x10000000 | _m1b;

    if (_M2PWMV >= 1510)
      CTRB = 0x10000000 | _m2a;

    if (_M2PWMV <= 1490)
      CTRB = 0x10000000 | _m2b;
    
    PCNT = CNT;
    m1 = abs(1500 - _M1PWMV) * 320; //scale to 2 milliseconds
    m2 = abs(1500 - _M2PWMV) * 320;
    
    PHSB = ~m1;
    PHSA = ~m2;
    
    while ((CNT - PCNT) < 160000); //wait 2 milliseconds
    
    PHSB = 0;
    PHSA = 0;
  }

  input(_m1a);
  input(_m1b);
  input(_m2a);
  input(_m2b);
}
  