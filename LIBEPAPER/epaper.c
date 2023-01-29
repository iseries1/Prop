/**
 * @brief Driver for e-Paper display
 * @author Michael Burmeister
 * @date July 7, 2019
 * @version 1.0
 * 
*/

#include "epaper.h"
#include "epaperreg.h"
#include "simpletools.h"

void spi_out(int, int);
void writeCmd(int);
int readCmd(int);
void drawLine(short, short, short, short, char);

int _DIN;
int _CLK;
int _CS;
int _DC;
int _RST;
int _BUSY;
int _DMask;
int _CMask;
int _Dmask;
int _Cmask;

unsigned char _Buffer[4736];

unsigned char lut[] = { 0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 0x66, 0x69,
                        0x69, 0x59, 0x58, 0x99, 0x99, 0x88, 0x00, 0x00, 0x00, 0x00,
                        0xF8, 0xB4, 0x13, 0x51, 0x35, 0x51, 0x51, 0x19, 0x01, 0x00};

// font 5x7 in 8x8 format line by line
long Font_57[] = {0x1f1f1f1f, 0x1f1f1f1f, //0x0
               0x07030101, 0x3f1f0f07, //0x1
               0x151b111f, 0x1f111b15, //0x2
               0x1c1e1e1f, 0x10101818, //0x3
               0x18040201, 0x01020418, //0x4
               0x1f000000, 0x0000001f, //0x5
               0x04040404, 0x04040404, //0x6
               0x1111111f, 0x1f111111, //0x7
               0x150a150a, 0x150a150a, //0x8
               0x150a150a, 0x150a150a, //0x9
               0x150a150a, 0x150a150a, //0xa
               0x150a150a, 0x150a150a, //0xb
               0x150a150a, 0x150a150a, //0xc
               0x150a150a, 0x150a150a, //0xd
               0x150a150a, 0x150a150a, //0xe
               0x150a150a, 0x150a150a, //0xf
               0x1f1f1f1f, 0x1f1f1f1f, //0x10
               0x071b1d1e, 0x1e1d1b07, //0x11
               0x00001f1f, 0x1f1f0000, //0x12
               0x11111111, 0x11111111, //0x13
               0x151b1b1f, 0x1f1b1b15, //0x14
               0x1313131f, 0x1f131313, //0x15
               0x1919191f, 0x1f191919, //0x16
               0x1111111f, 0x1f111111, //0x17
               0x1111111f, 0x1f111111, //0x18
               0x1111111f, 0x1f111111, //0x19
               0x1111111f, 0x1f111111, //0x1a
               0x1111111f, 0x1f111111, //0x1b
               0x1111111f, 0x1f111111, //0x1c
               0x1111111f, 0x1f111111, //0x1d
               0x1111111f, 0x1f111111, //0x1e
               0x1111111f, 0x1f111111, //0x1f
               0x00000000, 0x00000000, //0x20
               0x01010101, 0x00010001, //0x21
               0x0012091b, 0x00000000, //0x22
               0x0a1f0a00, 0x00000a1f, //0x23
               0x0e051e04, 0x00040f14, //0x24
               0x04081111, 0x00111102, //0x25
               0x02050502, 0x00160915, //0x26
               0x0004080c, 0x00000000, //0x27
               0x04040810, 0x00100804, //0x28
               0x04040201, 0x00010204, //0x29
               0x0e150400, 0x0004150e, //0x2a
               0x1f040400, 0x00000404, //0x2b
               0x00000000, 0x01020300, //0x2c
               0x1f000000, 0x00000000, //0x2d
               0x00000000, 0x00030300, //0x2e
               0x04081010, 0x00010102, //0x2f
               0x1519110e, 0x000e1113, //0x30
               0x04040604, 0x000e0404, //0x31
               0x0810110e, 0x001f0106, //0x32
               0x0e10110e, 0x000e1110, //0x33
               0x090a0c08, 0x0008081f, //0x34
               0x100f011f, 0x000e1110, //0x35
               0x0f01020c, 0x000e1111, //0x36
               0x0408101f, 0x00020202, //0x37
               0x0e11110e, 0x000e1111, //0x38
               0x1e11110e, 0x00060810, //0x39
               0x00030300, 0x00000303, //0x3a
               0x00030300, 0x01020303, //0x3b
               0x02040810, 0x00100804, //0x3c
               0x001f0000, 0x0000001f, //0x3d
               0x08040201, 0x00010204, //0x3e
               0x0810110e, 0x00040004, //0x3f
               0x1515110e, 0x001e010d, //0x40
               0x11110a04, 0x0011111f, //0x41
               0x0f11110f, 0x000f1111, //0x42
               0x0101120c, 0x000c1201, //0x43
               0x11110907, 0x00070911, //0x44
               0x0f01011f, 0x001f0101, //0x45
               0x0f01011f, 0x00010101, //0x46
               0x0101110e, 0x000e1119, //0x47
               0x1f111111, 0x00111111, //0x48
               0x0404041f, 0x001f0404, //0x49
               0x10101010, 0x000e1110, //0x4a
               0x03050911, 0x00110905, //0x4b
               0x01010101, 0x001f0101, //0x4c
               0x15151b11, 0x00111111, //0x4d
               0x15131111, 0x00111119, //0x4e
               0x1111110e, 0x000e1111, //0x4f
               0x0f11110f, 0x00010101, //0x50
               0x1111110e, 0x00160915, //0x51
               0x0f11110f, 0x00110905, //0x52
               0x0e01110e, 0x000e1110, //0x53
               0x0404041f, 0x00040404, //0x54
               0x11111111, 0x000e1111, //0x55
               0x0a111111, 0x0004040a, //0x56
               0x15111111, 0x000a1515, //0x57
               0x040a1111, 0x0011110a, //0x58
               0x040a1111, 0x00040404, //0x59
               0x0408101f, 0x001f0102, //0x5a
               0x0303031f, 0x001f0303, //0x5b
               0x04020101, 0x00101008, //0x5c
               0x1818181f, 0x001f1818, //0x5d
               0x0a040000, 0x00000011, //0x5e
               0x00000000, 0x1f000000, //0x5f
               0x000c0408, 0x00000000, //0x60
               0x100e0000, 0x001e111e, //0x61
               0x110f0101, 0x000f1111, //0x62
               0x011e0000, 0x001e0101, //0x63
               0x111e1010, 0x001e1111, //0x64
               0x110e0000, 0x001e011f, //0x65
               0x0f02120c, 0x00020202, //0x66
               0x110e0000, 0x0e101e11, //0x67
               0x110f0101, 0x00111111, //0x68
               0x04060004, 0x000e0404, //0x69
               0x080c0008, 0x06090808, //0x6a
               0x09110101, 0x00110906, //0x6b
               0x04040406, 0x000e0404, //0x6c
               0x151b0000, 0x00111515, //0x6d
               0x110f0000, 0x00111111, //0x6e
               0x110e0000, 0x000e1111, //0x6f
               0x110f0000, 0x01010f11, //0x70
               0x111e0000, 0x10101e11, //0x71
               0x031d0000, 0x00010101, //0x72
               0x011e0000, 0x000f100e, //0x73
               0x020f0202, 0x000c1202, //0x74
               0x11110000, 0x00161911, //0x75
               0x11110000, 0x00040a11, //0x76
               0x11110000, 0x001b1515, //0x77
               0x0a110000, 0x00110a04, //0x78
               0x11110000, 0x0e101e11, //0x79
               0x081f0000, 0x001f0204, //0x7a
               0x0306061c, 0x001c0606, //0x7b
               0x04040404, 0x04040404, //0x7c
               0x180c0c07, 0x00070c0c, //0x7d
               0x000d1600, 0x00000000, //0x7e
               0x1f1f1f1f, 0x1f1f1f1f}; //0x7f

int epaper_init(char din, char clk, char cs, char dc, char rst, char busy)
{
  int id;
  
  _DIN = din;
  _CLK = clk;
  _CS = cs;
  _DC = dc;
  _RST = rst;
  _BUSY = busy;
  
  _DMask = 1 << _DIN;
  _CMask = 1 << _CLK;
  _Dmask = ~_DMask;
  _Cmask = ~_CMask;
  
  high(_DIN);
  low(_CLK);
  high(_DC);
  input(_BUSY);
  
  low(_CS);
  low(_RST);
  pause(200);
  high(_RST);
  pause(200);
  
  while (input(_BUSY) == 1)
    pause(1);
  
  writeCmd(EPAPER_DRVOUT); // 296
  spi_out(8, 295);
  spi_out(8, 295 >> 8);
  spi_out(8, 0);
  
  writeCmd(EPAPER_BSTSFT); // d7, d6, 9d
  spi_out(8, 0xD7);
  spi_out(8, 0xD6);
  spi_out(8, 0x9D);

  writeCmd(EPAPER_WVCOM);
  spi_out(8, 0xA8);
  
  writeCmd(EPAPER_DUMMY);
  spi_out(8, 0x1A);
  
  writeCmd(EPAPER_GATE);
  spi_out(8, 0x08);
  
  writeCmd(EPAPER_DATA);
  spi_out(8, 0x03);
  
  writeCmd(EPAPER_WLUT);
  for (int i=0;i<30;i++)
    spi_out(8, lut[i]);
  
  while (input(_BUSY) == 1)
    pause(1);

  high(_CS);
  
  return id;
}

void epaper_sleep(char sleep)
{
  low(_CS);
  writeCmd(EPAPER_DEPSLP);
  spi_out(8, sleep & 0x01);
  high(_CS);
}

void epaper_update()
{
  low(_CS);
  
  writeCmd(EPAPER_SRAMX);
  spi_out(8, 0);
  spi_out(8, 15);
  
  writeCmd(EPAPER_SRAMY);
  spi_out(8, 0);
  spi_out(8, 0);
  spi_out(8, 295);
  spi_out(8, 295 >> 8);
  
  writeCmd(EPAPER_SRAMXC); //cursor
  spi_out(8, 0);
  
  writeCmd(EPAPER_SRAMYC); //cursor
  spi_out(8, 0);
  spi_out(8, 0);
  
  while (input(_BUSY) == 1)
    pause(1);

  writeCmd(EPAPER_WRAM);
  for (int i=0;i<4736;i++)
  {
    spi_out(8, _Buffer[i]);
  }

  writeCmd(EPAPER_UPDAT2);
  spi_out(8, 0xC4);
  
  writeCmd(EPAPER_MASTER);
  while (input(_BUSY) == 1)
    pause(1);
  
  writeCmd(EPAPER_NOP);
  
  high(_CS);
  

}

void epaper_cls(char color)
{
  int v;
  
  if (color == 0)
    v = 0;
  else
    v = 0xff;

  memset(_Buffer, v, sizeof(_Buffer));
  
  epaper_update();
}

void epaper_plot(short x, short y, char c)
{
  int d;
  int p;
  short b;
  
  p = 15 - (x / 8);
  p = p + y * 16;
  b = x % 8;
  b = 1 << b;
  d = _Buffer[p];

  if (c)
    _Buffer[p] = d | b;
  else
    _Buffer[p] = d & ~b;
}

unsigned char *epaper_buffer(void)
{
  return _Buffer;
}

void epaper_writeChar(short x, short y, char ch)
{
  long *base;
  int offset;
  long v;
  
  offset = ch & 0xfe; // Two characters per location
  base = (long*)(0x8000 + (offset << 6)); // jump to character position

  offset = 0;
  for (int i=0;i<32;i++)
  {
    v = base[offset++];
    if (ch & 0x01)
      v = v >> 1;
  
    for (int j=0;j<16;j++)
    {
      epaper_plot(x+i, y+j, (v & 0x01) ^ 1);
      v = v >> 2;
    }
  }    
}

void epaper_writeSChar(short x, short y, char ch)
{
  char t;
  long v;
  
  t = ch * 2;
  for (int l=0;l<2;l++)
  {
    v = Font_57[t++];
    for (int i=0;i<4;i++)
    {
      for (int j=0;j<8;j++)
      {
        epaper_plot(x, y+j, (v & 0x01) ^ 1);
        v = v >> 1;
      }
      x++;
    }
  }
}

void epaper_writeXChar(short x, short y, char c)
{
  long *base;
  int offset;
  long v;

  offset = c & 0xfe; // Two characters per location
  base = (long*)(0x8000 + (offset << 6)); // jump to character position

  offset = 0;
  for (int i=0;i<64;i++)
  {
    if ((i & 0x01) == 1)
      v = base[offset++];
    else
      v = base[offset];

    if (c & 0x01)
      v = v >> 1;
  
    for (int j=0;j<32;j++)
    {
      epaper_plot(x+i, y+j, (v & 0x01) ^ 1);
      if ((j & 0x01) == 1)
        v = v >> 2;
    }
  }
}

void epaper_writeStr(short x, short y, char *s)
{
  int i, v;
  
  i = 0;
  while ((y < 296) && (s[i] > 0))
  {
    v = s[i++];
    epaper_writeChar(x, y, v);
    y = y + 16;
  }
}

void epaper_writeSStr(short x, short y, char *s)
{
  int i, v;
  
  i = 0;
  while ((x < 128) && (s[i] > 0))
  {
    v = s[i++];
    epaper_writeSChar(x, y, v);
    y = y + 8;
  }
}

void epaper_writeXStr(short x, short y, char* s)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 128) && (s[i] > 0))
  {
    v = s[i++];
    epaper_writeXChar(x, y, v);
    y = y + 32;
  }
}

void epaper_drawLine(short x0, short y0, short x1, short y1, char c)
{
  short dx, dy, D, x, y, z;
  
  dx = x1 - x0;
  if (dx < 0)
  {
    x = x0;x0 = x1;x1 = x;
    y = y0;y0 = y1;y1 = y;
  }
  dx = abs(dx);
  dy = y1 - y0;
  if (dy < 0)
    z = -1;
  else
    z = 1;
  dy = abs(dy);
  if (dx < dy)
  {
    drawLine(x0, y0, x1, y1, c);
    return;
  }
  D = 2 * dy - dx;
  y = y0;
  
  for (x = x0;x <= x1;x++)
  {
    epaper_plot(x, y, c);
    if (D > 0)
    {
      y = y + z;
      D = D - 2 * dx;
    }
    D = D + 2 * dy;
  }          
}
  
void drawLine(short x, short y, short x1, short y1, char c)
{
  short dx, dy, D, xx, yy, z;
  
  dy = y1 - y;
  if (dy < 0)
  {
    yy = y;yy = y1;y1 = y;
    xx = x;xx = x1;x1 = x;
  }
  dy = abs(dy);
  dx = x1 - x;
  if (dx < 0)
    z = -1;
  else
    z = 1;
  dx = abs(dx);
  D = 2 * dx - dy;
  xx = x;
  
  for (yy = yy;yy <= y1;yy++)
  {
    epaper_plot(xx, yy, c);
    if (D > 0)
    {
      xx = xx + z;
      D = D - 2 * dy;
    }
    D = D + 2 * dx;
  }
}

void epaper_drawBox(short x, short y, short x1, short y1, char c)
{
  epaper_drawLine(x, y, x1, y, c);
  epaper_drawLine(x, y, x, y1, c);
  epaper_drawLine(x1, y, x1, y1, c);
  epaper_drawLine(x, y1, x1, y1, c);
}


// low level functions
void writeCmd(int cmd)
{
  low(_DC);
  spi_out(8, cmd); //shift_out(_DIN, _CLK, MSBFIRST, 8, cmd);
  high(_DC);
}

int readCmd(int cmd)
{
  int r;
  
  low(_DC);
  low(_CS);
  spi_out(8, cmd); //shift_out(_DIN, _CLK, MSBFIRST, 8, cmd);
  
  high(_DC);
  
//  r = shift_in(_DIN, _CLK, MSBPRE, 8);

  high(_CS);
  
  return r;
}

void __attribute__((fcache))spi_out(int bits, int value)
{
  unsigned long b;
  int i;
  
  b = 1 << (bits - 1);
  
  for(i = 0; i < bits; i++)
  {
    if ((value & b) != 0)
      OUTA |= _DMask;
    else
      OUTA &= _Dmask;
    OUTA &= _Cmask;
    OUTA |= _CMask;
    OUTA &= _Cmask;
    b = b >> 1;
  }
}

