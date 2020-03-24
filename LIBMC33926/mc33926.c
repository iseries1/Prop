/**
 * @brief Driver logic for MC33926 motor drive
 * @author Michael Burmeister
 * @date June 28, 2019
 * @version 1.0
 * 
*/

#include "mc33926.h"
#include "simpletools.h"

void domc33926(void *);


int _M2IN1;
int _M2IN2;
int _M1IN1;
int _M1IN2;
int _M2PWM;
int _M1PWM;
volatile int _M1PWMV;
volatile int _M2PWMV;
volatile int _RUNIT;

void mc33926_init(char m2in1, char m2in2, char m2pwm, char m1in1, char m1in2, char m1pwm)
{
  _M2IN1 = m2in1;
  _M2IN2 = m2in2;
  _M2PWM = m2pwm;
  _M1IN1 = m1in1;
  _M1IN2 = m1in2;
  _M1PWM = m1pwm;
  
  _M1PWMV = 1500; //all stop
  _M2PWMV = 1500; //all stop
  
  cog_run(&domc33926, 40);
  
}

void mc33926_setPWM(int motor1, int motor2)
{
  if (motor1 > 2000)
    motor1 = 2000;
  if (motor2 > 2000)
    motor2 = 2000;
  if (motor1 < 1000)
    motor1 = 1000;
  if (motor2 < 1000)
    motor2 = 1000;
  
  _M1PWMV = motor1;
  _M2PWMV = motor2;
}

void mc33926_stop(void)
{
  _RUNIT = 0;
}

void domc33926(void *par)
{
  long m1, m2;
  unsigned long PCNT;
  
  _RUNIT = 1;
  
  low(_M1PWM);
  low(_M2PWM);
  
  PHSA = 0;
  FRQA = 1;
  CTRA = 0x10000000 | _M2PWM;
  
  PHSB = 0;
  FRQB = 1;
  CTRB = 0x10000000 | _M1PWM;

  while (_RUNIT)
  {
    low(_M1IN1);
    low(_M1IN2);
    low(_M2IN1);
    low(_M2IN2);

    // create dead band and determine direction
    if (_M1PWMV >= 1510)
      high(_M1IN1);

    if (_M1PWMV <= 1490)
      high(_M1IN2);

    if (_M2PWMV >= 1510)
      high(_M2IN1);

    if (_M2PWMV <= 1490)
      high(_M2IN2);
    
    PCNT = CNT;
    m1 = abs(1500 - _M1PWMV) * 320; //scale to 2 milliseconds
    m2 = abs(1500 - _M2PWMV) * 320;
    
    PHSB = ~m1;
    PHSA = ~m2;
    
    while ((CNT - PCNT) < 160000); //wait 2 milliseconds
    
    PHSB = 0;
    PHSA = 0;
  }

  input(_M1PWM);
  input(_M2PWM);
}
