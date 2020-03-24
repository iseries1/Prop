/**
 * @brief Colored Oled Display Driver
 * @author Michael Burmeister
 * @date December 11, 2018
 * @version 1.0
 * 
*/
#include "ssd1331.h"
#include "ssd1331reg.h"
#include "simpletools.h"

void SSD1331_cmd(char);
void SSD1331_write(char);

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

char _DIN;
char _CLK;
char _CS;
char _DC;
char _RES;
char _rotation;
unsigned short _FG;
unsigned short _BG;

void SSD1331_init(char din, char clk, char cs, char dc, char res)
{
  _DIN = din;
  _CLK = clk;
  _CS = cs;
  _DC = dc;
  _RES = res;
  
  low(_RES);
  pause(100);
  high(_RES);
  pause(100);
  low(_RES);
  pause(100);
  high(_RES);
  
  low(_CS);
  SSD1331_cmd(SSD1331_DISPLAYOFF); //reset has display off
  SSD1331_cmd(SSD1331_SETREMAP);
  SSD1331_cmd(0x60);
  SSD1331_cmd(SSD1331_STARTLINE); // reset set to 00
  SSD1331_cmd(0x00);
  SSD1331_cmd(SSD1331_DISPLAYOFFSET); // reset set to 00
  SSD1331_cmd(0x00);
  SSD1331_cmd(SSD1331_NORMALDISPLAY); // reset does this
  SSD1331_cmd(SSD1331_SETMULTIPLEX); // reset set this 64
  SSD1331_cmd(0x3f);
  SSD1331_cmd(SSD1331_SETMASTER);
  SSD1331_cmd(0x8E);
  SSD1331_cmd(SSD1331_POWERMODE);
  SSD1331_cmd(0x0B);
  SSD1331_cmd(SSD1331_PRECHARGE);
  SSD1331_cmd(0x31);
  SSD1331_cmd(SSD1331_CLOCKDIV);
  SSD1331_cmd(0xF0);
  SSD1331_cmd(SSD1331_PRECHARGEA);
  SSD1331_cmd(0x64);
  SSD1331_cmd(SSD1331_PRECHARGEB);
  SSD1331_cmd(0x78);
  SSD1331_cmd(SSD1331_PRECHARGEC);
  SSD1331_cmd(0x64);
  SSD1331_cmd(SSD1331_PRECHARGELEVEL);
  SSD1331_cmd(0x3A);
  SSD1331_cmd(SSD1331_VCOMH);
  SSD1331_cmd(0x3E);
  SSD1331_cmd(SSD1331_MASTERCURRENT);
  SSD1331_cmd(0x06);
  SSD1331_cmd(SSD1331_CONTRASTA); // reset set 128
  SSD1331_cmd(128);
  SSD1331_cmd(SSD1331_CONTRASTB); // reset set 128
  SSD1331_cmd(128);
  SSD1331_cmd(SSD1331_CONTRASTC); // reset set 128
  SSD1331_cmd(128);
  SSD1331_cmd(SSD1331_DIMCONTRAST); // dim contrast
  SSD1331_cmd(0x00);
  SSD1331_cmd(63); // color a
  SSD1331_cmd(63); // color b
  SSD1331_cmd(63); // color c
  SSD1331_cmd(15);
  
  _FG = 0xffff;
  _BG = 0x00;
  
  SSD1331_rotation(0);
  SSD1331_cls();
  SSD1331_display(1);

}

void SSD1331_rotation(char r)
{
  short v = 0;
  
  switch (r)
  {
    case 0: v = 0x60; //right side up
            break;
    case 1: v = 0x72; //upside down
            break;
  }
  SSD1331_cmd(SSD1331_SETREMAP);
  SSD1331_cmd(v);
  
  _rotation = r;
}  

void SSD1331_cls()
{
  SSD1331_cmd(SSD1331_CLEAR);
  SSD1331_cmd(0x00); // x
  SSD1331_cmd(0x00); // y
  SSD1331_cmd(TFTWIDTH-1); // x
  SSD1331_cmd(TFTHEIGHT-1); // y
  
  pause(25);
}

void SSD1331_invert(short i)
{
  switch (i)
  {
    case 1: i = SSD1331_INVERTDISPLAY;
            break;
    case 2: i = SSD1331_DISPLAYALLON;
            break;
    case 3: i = SSD1331_DISPLAYALLOFF;
            break;
    default: i = SSD1331_NORMALDISPLAY;
  }
  
  SSD1331_cmd(i);
}

unsigned short SSD1331_color(char r, char g, char b)
{
  unsigned short c;
  
  c = r & 0x1f;
  c = (c << 6) | (g & 0x2f);
  c = (c << 5) | (b & 0x1f);
  return c;
}
  
void SSD1331_plot(short x, short y, unsigned short z)
{
  if (x >= TFTWIDTH)
    return;
  if (y >= TFTHEIGHT)
    return;

  SSD1331_cmd(SSD1331_SETCOLUMN);
  SSD1331_cmd(x);
  SSD1331_cmd(TFTWIDTH-1);
  SSD1331_cmd(SSD1331_SETROW);
  SSD1331_cmd(y);
  SSD1331_cmd(TFTHEIGHT-1);
  SSD1331_write(z >> 8);
  SSD1331_write(z);
}

void SSD1331_textColor(unsigned short f, unsigned short b)
{
  _FG = f;
  _BG = b;
}
  
void SSD1331_writeChar(char x, char y, char c)
{
  long *base;
  int offset;
  long v;
  
  offset = c & 0xfe; // Two characters per location
  base = (long*)(0x8000 + (offset << 6)); // jump to character position

  offset = 0;
  for (int i=0;i<32;i++)
  {
    v = base[offset++];
    if (c & 0x01)
      v = v >> 1;
  
    for (int j=0;j<16;j++)
    {
      if ((v & 0x01) == 1)
        SSD1331_plot(x+j, y+i, _FG);
      else
        SSD1331_plot(x+j, y+i, _BG);
      v = v >> 2;
    }
  }
}

void SSD1331_writeStr(char x, char y, char *c)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 16) && (c[i] > 0))
  {
    v = c[i++];
    SSD1331_writeChar(x, y, v);
    if (i == 8)
    {
      y = y + 32;
      x = x1;
    }
    else
      x = x + 16;
  }
}

void SSD1331_writeSChar(char x, char y, char c)
{
  char t;
  long v;
  
  t = c * 2;
  for (int l=0;l<2;l++)
  {
    v = Font_57[t++];
    for (int i=0;i<4;i++)
    {
      for (int j=0;j<8;j++)
      {
        if ((v & 0x01) == 1)
          SSD1331_plot(x+j, y, _FG);
        else
          SSD1331_plot(x+j, y, _BG);
        v = v >> 1;
      }
      y++;
    }
  }
}

void SSD1331_writeSStr(char x, char y, char *c)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 32) && (c[i] > 0))
  {
    v = c[i++];
    SSD1331_writeSChar(x, y, v);
    if (i == 16)
    {
      y = y + 8;
      x = x1;
    }
    else
      x = x + 8;
  }
}

void SSD1331_drawLine(short x, short y, short x1, short y1, unsigned short color)
{
  if (x >= TFTWIDTH)
    return;
  if (y >= TFTHEIGHT)
    return;
  if (x1 >= TFTWIDTH)
    x1 = TFTWIDTH - 1;
  if (y1 >= TFTHEIGHT)
    y1 = TFTHEIGHT - 1;
  
  SSD1331_cmd(SSD1331_DRAWLINE);
  SSD1331_cmd(x);
  SSD1331_cmd(y);
  SSD1331_cmd(x1);
  SSD1331_cmd(y1);
  SSD1331_cmd(color >> 10 & 0x3e);
  SSD1331_cmd(color >> 5 & 0x3f);
  SSD1331_cmd(color << 1 &0x3e);
}

void SSD1331_drawBox(short x, short y, short x1, short y1, unsigned short color)
{
  if (x >= TFTWIDTH)
    return;
  if (y >= TFTHEIGHT)
    return;
  if (x1 >= TFTWIDTH)
    x1 = TFTWIDTH - 1;
  if (y1 >= TFTHEIGHT)
    y1 = TFTHEIGHT - 1;
  
  SSD1331_cmd(SSD1331_DRAWRECT);
  SSD1331_cmd(x);
  SSD1331_cmd(y);
  SSD1331_cmd(x1);
  SSD1331_cmd(y1);
  SSD1331_cmd(color >> 10 & 0x3e);
  SSD1331_cmd(color >> 5 & 0x3f);
  SSD1331_cmd(color << 1 &0x3e);
  SSD1331_cmd(_BG >> 10 & 0x3e);
  SSD1331_cmd(_BG >> 5 & 0x3f);
  SSD1331_cmd(_BG << 1 & 0x3f);
}

void SSD1331_drawFilledBox(short x, short y, short x1, short y1, unsigned short c, unsigned short f)
{
  unsigned short i;
  
  SSD1331_cmd(SSD1331_FILL);
  SSD1331_cmd(0x01);
  i = _BG;
  _BG = f;
  SSD1331_drawBox(x, y, x1, y1, c);
  _BG = i;
  SSD1331_cmd(SSD1331_FILL);
  SSD1331_cmd(0x00);
}

void SSD1331_scrollRight(char o, char s, char e, char f)
{
  if (o > 47)
    o = 47;
  if (s+e > 64)
    e = 64 - s;
  SSD1331_cmd(SSD1331_SCROLLSETUP);
  SSD1331_cmd(o); //column offset
  SSD1331_cmd(s); //row start
  SSD1331_cmd(e); //number of rows
  SSD1331_cmd(0x00); //row offset
  SSD1331_cmd(f); //speed
  SSD1331_cmd(SSD1331_SCROLLSTART);
}

void SSD1331_scrollLeft(char o, char s, char e, char f)
{
  if (o > 47)
    o = 47;
  o = 96 - o;
  if (s+e > 64)
    e = 64 - s;
  SSD1331_cmd(SSD1331_SCROLLSETUP);
  SSD1331_cmd(o); //column offset
  SSD1331_cmd(s); //row start
  SSD1331_cmd(e); //number of rows
  SSD1331_cmd(0x00); //row offset
  SSD1331_cmd(f); //speed
  SSD1331_cmd(SSD1331_SCROLLSTART);
}

void SSD1331_scrollUp(char o, char f)
{
  if (o > 31)
    o = 31;
  SSD1331_cmd(SSD1331_SCROLLSETUP);
  SSD1331_cmd(0x00); //column offset
  SSD1331_cmd(0x00); //row start
  SSD1331_cmd(0x00); //number of rows
  SSD1331_cmd(o); //row offset
  SSD1331_cmd(f); //speed
  SSD1331_cmd(SSD1331_SCROLLSTART);
}

void SSD1331_scrollDown(char o, char f)
{
  if (o > 31)
    o = 31;
  o = 64 - o;
  SSD1331_cmd(SSD1331_SCROLLSETUP);
  SSD1331_cmd(0x00); //column offset
  SSD1331_cmd(0x00); //row start
  SSD1331_cmd(0x00); //number of rows
  SSD1331_cmd(o); //row offset
  SSD1331_cmd(f); //speed
  SSD1331_cmd(SSD1331_SCROLLSTART);
}

void SSD1331_display(char s)
{
  short v;
  
  switch (s)
  {
    case 0: v = SSD1331_DISPLAYOFF;
            break;
    case 1: v = SSD1331_DISPLAYON;
            break;
    case 2: v = SSD1331_DISPLAYDIM;
            break;
    default: v = SSD1331_DISPLAYOFF;
  }
  
  SSD1331_cmd(v);
}

void SSD1331_scrollStop(void)
{
  SSD1331_cmd(SSD1331_SCROLLSTOP);
}  

/* @brief write command
 * @param command
 */
void SSD1331_cmd(char cmd)
{
  low(_DC);
  SSD1331_write(cmd);
  high(_DC);
}

/* @brief write data
 * @param data
 */
void SSD1331_write(char data)
{
  shift_out(_DIN, _CLK, MSBFIRST, 8, data);
}
