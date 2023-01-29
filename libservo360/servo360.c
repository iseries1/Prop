/**
 * @file servo360.c
 * @brief Drive Servo 360 
 * @author Michael Burmeister
 * @date January 20, 2018
 * @version 1.0
*/
#include "simpletools.h"

volatile struct S360 {
  short Servo;
  short FeedBack;
  short Angle;
  short PAngle;
  short TAngle;
  short Turns;
  short TError;
  short PWM;
} S[9];

void doS360(void *);
void doServo(void *);
void getAngle(struct S360*);
void updatePos(struct S360*);
float doPID(struct S360*);
void changeCheck(void);
void HiLow(void);

static float Kp, Ki, Kd;
static unsigned long PCNT;
static int Count;

void S360_start()
{
  Kp = .5;
  Ki = .06;
  Kd = .1;
  
  for (int i=0;i<9;i++)
  {
    S[i].Servo = -1;
    S[i].FeedBack = -1;
    S[i].Angle = 0;
    S[i].PAngle = -1;
    S[i].TAngle = 0;
    S[i].Turns = 0;
    S[i].TError = 0;
    S[i].PWM = 0;
  }
  S[8].FeedBack = -2;
  cog_run(&doS360, 50);
  cog_run(&doServo, 50);
}

void S360_add(short s, short f)
{
  S[8].Servo = s;
  S[8].FeedBack = f;
  while (S[8].Servo == s);
}

void S360_remove(short s, short f)
{
  S[8].Servo = s;
  S[8].FeedBack = -1;
}

void S360_setAngle(short s, short a)
{
  for (int i=0;i<8;i++)
  {
    if (S[i].Servo == s)
    {
      S[i].TAngle = a;
      return;
    }
  }
}            

short S360_getAngle(short s)
{
  for (int i=0;i<8;i++)
  {
    if (S[i].Servo == s)
    {
      return S[i].Angle;
    }
  }
  return -1;
}
            
void changeCheck()
{
  // remove servo
  if (S[8].FeedBack == -1)
  {
    for (int i=0;i<8;i++)
      if (S[i].Servo == S[8].Servo)
      {
        input(S[i].Servo);
        S[i].Servo = -1;
        S[i].FeedBack = -1;
        S[i].PAngle = -1;
        S[i].Turns = 0;
        S[i].TAngle = 0;
        S[i].PWM = 0;
        S[8].Servo = -1;
        S[8].FeedBack = -2;
      }
    return;
  }

  // add servo
  if (S[8].FeedBack >= 0)
  {
    for (int i=0;i<8;i++)
      if (S[i].Servo == -1)
      {
        S[i].Servo = S[8].Servo;
        S[i].FeedBack = S[8].FeedBack;
        S[8].Servo = -1;
        S[8].FeedBack = -2;
        return;
      }
  }
}
  
void doS360(void *par)
{
  int index;
  
  index = 0;
  millis(&PCNT);
  Count = 0;
  while (1)
  {
    if (S[index].Servo >= 0)
    {
      getAngle(&S[index]);
      updatePos(&S[index]);
    }
    if (++index >= 8)
    {
      Count += millis(&PCNT);
      if (Count < 20)
        pause(20-Count);
      Count = 0;
      index = 0;
      changeCheck();
    }
  }          
}

void updatePos(struct S360 *s)
{
  int diff;
  
  if (s->TAngle < 0)
  {
    s->PWM = 0;
    return;
  }    

  diff = doPID(s);
    
  if (abs(diff) < 2)
  {
    s->PWM = 1500;
    return;
  }
  if (diff < 0)
    s->PWM = 1470 + diff;
  if (diff > 0)
    s->PWM = 1530 + diff;
}
    
void getAngle(struct S360 *s)
{
  unsigned long SLow, SHigh, STotal;
  
  if (s->PAngle < 0)
  {
    input(s->FeedBack);
    low(s->Servo);
  }
      
  CTRA = 0x30000000 | s->FeedBack; // get low count
  CTRB = 0x20000000 | s->FeedBack; // get high count
  FRQA = 1;
  FRQB = 1;
  if (1)
  {
    while (get_state(s->FeedBack) == 0);  // wait till high
    PHSA = 0;
    while (PHSA == 0);
    PHSB = 0;
    while (get_state(s->FeedBack) == 0);
    SLow = PHSA;
    while (get_state(s->FeedBack) == 1);
    SHigh = PHSB;
    SLow = SLow/80; // In Microseconds
    SHigh = SHigh/80; // In Microseconds
    STotal = SLow + SHigh;
    if ((STotal < 1180) && (STotal > 1050))
      s->Angle = (SLow*1000/STotal-29)*360/943;
    if (s->PAngle < 0)
    {
      s->PAngle = s->Angle;
      s->TAngle = s->Angle;
    }      
    if ((s->Angle < 10) && (s->PAngle > 350))
      s->Turns++;
    if ((s->Angle > 350) && (s->PAngle < 10))
      s->Turns--;
    s->PAngle = s->Angle;
  }
}

float doPID(struct S360 *s)
{
  
  float err = s->TAngle - (s->Turns*360 + s->Angle);
  int Pe = s->TAngle - (s->Turns*360 + s->PAngle);
  s->TError = s->TError + err;
  if (s->TError > 300)
    s->TError = 300;
  if (s->TError < -300)
    s->TError = -300;
  float x = Kp * err + Ki * s->TError - Kd * Pe;
  return x;
}

long S360_getCount()
{
  return Count;
}

void HiLow()
{
  if (get_state(26) == 0)
    high(26);
  else
    low(26);
}

void doServo(void *par)
{
  long Mask;
  
  CTRA = 0;
  CTRB = 0;
  PHSA = 0;
  PHSB = 0;
  FRQA = 1;
  FRQB = 1;
  
  int i;
  
  while (1)
  {
    PHSB = 0;
    CTRB = 0x7C000000;
    for (i=0;i<8;i++)
    {
      if (S[i].Servo >= 0)
      {
        low(S[i].Servo);
        Mask = 1 << S[i].Servo;
        PHSA = -S[i].PWM * us;
        CTRA = 0x10000000 | S[i].Servo;
        waitpeq(0, Mask);
        CTRA = 0;
      }
    }
    while (PHSB < 1600000);
    CTRB = 0;
  }    
}
  