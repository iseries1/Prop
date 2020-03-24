/**
 * @brief SBus receiver decoder
 * @author Michael Burmeister
 * @date December 13, 2017
 * @version 1.1
 * 
*/

#include "simpletools.h"
#include "SBus.h"

void doRecSBus(void *);
void doChannel(void);

int _Dc[26];
int _Cc[17];
int _Cmn[17];
int _Cmx[17];
int _Er;
int _SBPin;
int _Lock;

int SBus_open(char p)
{
  int *cog;
  
  memset(_Cc, 0, sizeof(_Cc));
  
  for (int i=0;i<17;i++)
  {
    _Cmn[i] = 200;
    _Cmx[i] = 1750;
  }
  
  _SBPin = p;
  *cog = 0;
  cog = cog_run(&doRecSBus, 50);
  _Lock = locknew();
  if (_Lock < 0)
    return -1;
  if (*cog == 0)
    return -1;
  else
    return 0;
}

void doRecSBus(void *par)
{
  int rxmask;
  int rxbits;
  int rxdata;
  int baud;
  int wcnt;
  int c;
  
  rxmask = 1 << _SBPin;
  baud = 800;
  c = 0;
  
  while (1)
  {
    waitpne(0, rxmask);       // Wait for Start Bit
    rxbits = 10;
    rxdata = 0;
    wcnt = baud >> 1;
    wcnt = wcnt + CNT;
    while (rxbits > 0)
    {
      wcnt += baud;
      waitcnt2(wcnt, baud);   // Wait for Center of Next bit
      rxdata = rxdata << 1;
      if ((rxmask & INA) != rxmask)  // Reverse Bit value
        rxdata = rxdata | 1;

      rxbits--;
    }
    rxdata = rxdata >> 2;    // Dump Parity and Stop
    if (rxdata == 0xf0)      // SBus Start Byte Frame value
      c = 0;
    _Dc[c] = rxdata;
    if (c++ > 25)            // Just in case
      c = 25;
    if (c == 24)
      doChannel();
  }
}

void doChannel()
{
  int i;
  short c, b, bc;
  
  c = 0;         // Channel
  b = 0x80;      // Bit Position high -> low
  bc = 1;        // Bit Channel value
  i = 1;         // Should be 1
  while (lockset(_Lock));
  _Cc[0] = 0;      // Clear Channel value
  while (c < 16) // Do 16 Channels
  {
    if ((_Dc[i] & b) == b)
      _Cc[c] |= bc;
    b = b >> 1;
    if (b == 0)
    {
      b = 0x80;
      i++;
    }
    bc = bc << 1;
    if (bc > 0x400)
    {
      bc = 1;
      c++;
      _Cc[c] = 0;
    }
  }
  lockclr(_Lock);
  _Er = 0;
  if (_Dc[23] == 0x20)
    _Er = 1;
  if (_Dc[23] == 0x30)
    _Er = -1;
}

short SBus_getChannel(char c)
{
  int v;
  
  if ((c > 16) || (c < 1))
    return -1;

  while (lockset(_Lock));
  v = _Cc[c-1];
  lockclr(_Lock);
  return v;
}

short SBus_getAdjChannel(char c)
{
  int v;
  
  if ((c > 16) || (c < 1))
    return -1;

  while (lockset(_Lock));
  v = _Cc[c-1] * 10/16 + 875;
  lockclr(_Lock);
  return v;
}

short SBus_getStatus()
{
  return _Er;
}

int SBus_getScaledChannel(char c)
{
  int i;
  
  if ((c > 16) || (c < 1))
    return -1;

  c = c - 1;
  while (lockset(_Lock));
  i = _Cc[c];
  lockclr(_Lock);
  
  i = 1000*(i - _Cmn[c])/(_Cmx[c] - _Cmn[c])+1000;
  return i;
}

void SBus_setScaledChannel(char c, int min, int max)
{
  if ((c > 16) || (c < 1))
    return;
  
  _Cmn[c-1] = min;
  _Cmx[c-1] = max;
}
  