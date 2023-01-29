/**
 * @brief Motor Driver for Adafruit TB6612
 * @author Michael Burmeister
 * @date May 3, 2020
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "tb6612.h"

void TB6612(void *);


static int AIN1;
static int AIN2;
static int BIN1;
static int BIN2;
static int PWMA;
static int PWMB;
static volatile int PWMAV;
static volatile int PWMBV;
static volatile int RUNSTOP;

void tb6612_init(int ain1, int ain2, int pwma, int bin1, int bin2, int pwmb)
{
  AIN1 = ain1;
  AIN2 = ain2;
  PWMA = pwma;
  BIN1 = bin1;
  BIN2 = bin2;
  PWMB = pwmb;
  PWMAV = 1500; // All stop
  PWMBV = 1500; // All stop
  
  cog_run(&TB6612, 40);
}

void tb6612_setPWM(int motora, int motorb)
{
  if (motora > 2000)
    motora = 2000;
  if (motora < 1000)
    motora = 1000;
  if (motorb > 2000)
    motorb = 2000;
  if (motorb < 1000)
    motorb = 1000;
  
  PWMAV = motora;
  PWMBV = motorb;
}

void tb6612_shutdown()
{
  RUNSTOP = 0;
}

void TB6612(void *par)
{
  long ma, mb;
  unsigned long PCNT;
  
  RUNSTOP = 1;
  
  low(PWMA);
  low(PWMB);
  
  PHSA = 0;
  FRQA = 1;
  CTRA = 0x10000000 | PWMA;
  
  PHSB = 0;
  FRQB = 1;
  CTRB = 0x10000000 | PWMB;
  
  while (RUNSTOP)
  {
    low(AIN1);
    low(AIN2);
    low(BIN1);
    low(BIN2);
    
    if (PWMAV >= 1510)
      high(AIN1);
    if (PWMAV <= 1490)
      high(AIN2);
    if (PWMBV >= 1510)
      high(BIN1);
    if (PWMBV <= 1490)
      high(BIN2);
    
    PCNT = CNT;
    ma = abs(1500 - PWMAV) * 320; // scale to 2 milliseconds
    mb = abs(1500 - PWMBV) * 320;
    
    PHSA = ~ma;
    PHSB = ~mb;
    
    while ((CNT - PCNT) < 160000); // wait 2 milliseconds
    
    PHSA = 0;
    PHSB = 0;
  }
  
  input(PWMAV);
  input(PWMBV);
}
        