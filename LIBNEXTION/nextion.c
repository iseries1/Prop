/**
 * @brief Interface to Nextion display
 * @author Michael Burmeister
 * @date December 21, 2017
 * @version 1.1
 * 
*/

#include "nextion.h"
#include "simpletools.h"
#include "fdserial.h"

void Nextion_connect(void);
void Nextion_return(void);
void Nextion_value(void);
void Nextion_button(void);
void Nextion_sendme(void);
void Nextion_touch(void);
void Nextion_sleep(void);
void Nextion_wake(void);
void Nextion_text(void);
void Nextion_numeric(void);
void dorecv(void *);


fdserial *nxn;
unsigned char _DataT[128];
int _Index;
int _Error;
int  _Reserved;
char _Model[20];
int _Firmware = 0;
int _MCUSize = 0;
char _SerialNumber[20];
int _Flash = 0;
int _Page = 0;
int _Button = 0;
int _Event = 0;
int _XPosition = 0;
int _YPosition = 0;
int _Sleep = 0;
char _Text[50];
int _Value = 0;


int *cog;


int Nextion_open(int rx, int tx, int baud)
{
  int i;
  
  nxn = fdserial_open(rx, tx, FDSERIAL_MODE_NONE, baud);
  
  _Error = -1;
  
  cog = cog_run(&dorecv, 50);
  
  pause(1000);
  
  Nextion_cmd("connect");
  
  pause(1000);
  
  i = _Reserved;
  
  return i;
}

void Nextion_close()
{
  fdserial_close(nxn);
  nxn = NULL;
}
  
void Nextion_cmd(char *c)
{
  int i = 0;
  _Index = 0;
  
  for (i=0;i<strlen(c);i++)
    fdserial_txChar(nxn, c[i]);

  fdserial_txChar(nxn, 0xff);
  fdserial_txChar(nxn, 0xff);
  fdserial_txChar(nxn, 0xff);
}

void Nextion_return()
{
  int i, j;
  
  if (_Index < 1)
    return;
  for (i=0;i<_Index;i++)
  {
    if (_DataT[i] == 0xff)
      if (_DataT[i+1] == 0xff)
        if (_DataT[i+2] == 0xff)
          Nextion_value();
  }
}

void Nextion_value()
{
  char v;
  
  v = _DataT[0];
  
  switch (v)
  {
    case 0x00: _Error = 0; //Invalid instruction
      break;
    case 0x01: _Error = 1; //Success
      break;
    case 0x02: _Error = 2; //Component ID invalid
      break;
    case 0x03: _Error = 3; //Page ID invalid
      break;
    case 0x04: _Error = 4; //Picture ID invalid
      break;
    case 0x05: _Error = 5; //Font ID invalid
      break;
    case 0x11: _Error = 17; //Baud rate settings invalid
      break;
    case 0x12: _Error = 18; //Curve control ID number or channel number is invalid
      break;
    case 0x1a: _Error = 26; //Variable name invalid
      break;
    case 0x1b: _Error = 27; //Variable operation invalid
      break;
    case 0x1c: _Error = 28; //Failed to assign
      break;
    case 0x1d: _Error = 29; //Operate EEPROM failed
      break;
    case 0x1e: _Error = 30; //Parameter quantity invalid
      break;
    case 0x1f: _Error = 31; //IO operation failed
      break;
    case 0x20: _Error = 32; //Undefined escape characters
      break;
    case 0x23: _Error = 35; //Too long variable name
      break;
    case 0x24: // serial buffer overflow
      break;
    case 0x63: Nextion_connect(); // process connect command
      break;
    case 0x65: Nextion_button(); // process object touch
      break;
    case 0x66: Nextion_sendme(); // process sendme command
      break;
    case 0x67: Nextion_touch(); // process touch event
      break;
    case 0x68: Nextion_touch(); // process sleep event
      break;
    case 0x70: Nextion_text(); // process text value
      break;
    case 0x71: Nextion_numeric(); // process number value
      break;
    case 0x86: Nextion_sleep(); // process panel sleep
      break;
    case 0x87: Nextion_wake(); // process panel wake
      break;
    case 0x88: // process panel power on
    case 0x89: // process sd card load
    case 0xfd: // transparent mode ending
    case 0xfe: // transparent mode starting
      break;
    default: _Error = 0;
  }
  _Index = 0;
}

void Nextion_connect()
{
  int i, j, k;
  
 _Reserved = 0;
 _Model[0] = 0;
 _Firmware = 0;
 _MCUSize = 0;
 _SerialNumber[0] = 0;
 _Flash = 0;
 
 i = 0;
 for (k=0;k<_Index;k++)
 {
   if (_DataT[k] == ',')
   {
     j = 0;
     i++;
     k++;
   }     
   switch (i)
   {
     case 0 :
      break;
     case 1 : _Reserved = _Reserved * 10 + _DataT[k] - '0';
      break;
     case 2 : _Model[j++] = _DataT[k];
              _Model[j] = 0;
      break;
     case 3 : _Firmware = _Firmware * 10 + _DataT[k] - '0';
      break;
     case 4 : _MCUSize = _MCUSize * 10 + _DataT[k] - '0';
      break;
     case 5 : _SerialNumber[j++] = _DataT[k];
              _SerialNumber[j] = 0;
      break;
     case 6 : _Flash = _Flash * 10 + _DataT[k] - '0';
      break;
    }
  }
}

int Nextion_error()
{
  int i;
  
  i = _Error;
  _Error = -1;
  return i;
}

void dorecv(void *par)
{
  while (nxn != NULL)
  {
    if (fdserial_rxReady(nxn) > 0)
    {
      _DataT[_Index] = fdserial_rxChar(nxn);
      if (_Index++ > 100)
        _Index = 100;
      _DataT[_Index] = 0;
    }
    Nextion_return();

    pause(1);
  }
  cogstop(cogid());
}

void Nextion_button()
{
  _Page = _DataT[1];
  _Button = _DataT[2];
  _Event = _DataT[3];
}

void Nextion_sendme()
{
  _Page = _DataT[1];
}

void Nextion_touch()
{
  _XPosition = _DataT[1];
  _XPosition = _XPosition << 8 | _DataT[2];
  _YPosition = _DataT[3];
  _YPosition = _YPosition << 8 | _DataT[4];
  _Event = _DataT[5];
}

void Nextion_sleep()
{
  _Sleep = 1;
}

void Nextion_wake()
{
  _Sleep = 0;
}

void Nextion_text()
{
  int i, j;
  
  j = 0;
  for (i=1;i<50;i++)
  {
    if (_DataT[i] == 0xff)
      break;
    _Text[j++] = _DataT[i];
  }
  _Text[j] = 0;
}

void Nextion_numeric()
{
  _Value = _DataT[4];
  _Value = _Value << 8 | _DataT[3];
  _Value = _Value << 8 | _DataT[2];
  _Value = _Value << 8 | _DataT[1];
}

char *Nextion_serialno()
{
  return _SerialNumber;
}

int Nextion_page(void)
{
  return _Page;
}

int Nextion_getnumeric()
{
  return _Value;
}

char *Nextion_gettext()
{
  return _Text;
}

void Nextion_settext(char *var, char *val)
{
  sprinti(_DataT, "%s.txt=\"%s\"", var, val);
  Nextion_cmd(_DataT);
}
  
void Nextion_setnumeric(char *var, int val)
{
  sprinti(_DataT, "%s.val=%d", var, val);
  Nextion_cmd(_DataT);
}

void Nextion_setbaud(int baud)
{
  sprinti(_DataT, "baud=%d", baud);
  Nextion_cmd(_DataT);
  Nextion_close();
}

void Nextion_setsleep(int t)
{
  sprinti(_DataT, "thsp=%d", t);
  Nextion_cmd(_DataT);
  if (t == 0)
    Nextion_cmd("thup=0");
  else
    Nextion_cmd("thup=1");
}

void Nextion_setbrightness(int b)
{
  sprinti(_DataT, "dim=%d", b);
  Nextion_cmd(_DataT);
}
  
void Nextion_xstr(short x, short y, short w, short h, char f, int pco, int bco, char xcen, char ycen, char sta, char *text)
{
  sprinti(_DataT, "xstr %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,\"%s\"", x, y, w, h, f,
          pco, bco, xcen, ycen, sta, text);
  Nextion_cmd(_DataT);
}

void Nextion_click(char *item, char value)
{
  sprinti(_DataT, "click %s,%d", item, value);
  Nextion_cmd(_DataT);
}
