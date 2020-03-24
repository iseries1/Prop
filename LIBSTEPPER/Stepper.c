/**
 * @brief Stepper Motor Driver logic
 * @author Michael Burmeister
 * @date March 14, 2019
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "Stepper.h"


int _EA, _EB;
int _DA, _DB;
int _SA, _SB;

void Stepper_init(char enableA, char directionA, char stepA, char enableB, char directionB, char stepB)
{
  _EA = enableA;
  _EB = enableB;
  _DA = directionA;
  _DB = directionB;
  _SA = stepA;
  _SB = stepB;
  
  high(_EA);
  high(_EB);
  high(_DA);
  high(_DB);
  low(_SA);
  low(_SB);
  
  PHSA = 0;
  FRQA = 0x00000000;
  CTRA = 0x10000000 | _SA;
  
  PHSB = 0;
  FRQB = 0x00000000;
  CTRB = 0x10000000 | _SB;

}

void Stepper_enable(char enable)
{
  if (enable == 0)
  {
    high(_EA);
    high(_EB);
  }
  else
  {
    low(_EA);
    low(_EB);
  }
  low(_SA);
  low(_SB);    
}

void Stepper_single(char motorA, char motorB)
{
  if (motorA != 0)
  {
    FRQA = 0x00000000;
    high(_SA);
    //pause(1);
    low(_SA);
  }
  
  if (motorB != 0)
  {
    FRQB = 0x00000000;
    high(_SB);
    //pause(1);
    low(_SB);
  }
}

void Stepper_direction(char directionA, char directionB)
{
  if (directionA == 1)
    low(_DA);
  if (directionA == 2)
    high(_DA);
    
  if (directionB == 1)
    low(_DB);
  if (directionB == 2)
    high(_DB);
}

void Stepper_speed(short speedA, short speedB)
{
  int A, B;
  
  A = speedA * 5369; // 80Mhz to even 10Hz
  B = speedB * 5369;
  FRQA = A;
  FRQB = B;
  // printi("Frequency: %d\n", S);
}
