/**
 * @brief SSD1306 Display Driver
 * @author Michael Burmeister
 * @date March 14, 2018
 * @version 1.0
 */

#include "simpletools.h"
#include "SSD1306.h"

void drawLine(short, short, short, short, char);


int _CS;
int _DC;
int _SDA;
int _SCL;
int _RST;
int _Auto;
int _Width;
int _Height;
char _Buffer[LCD_BUFFER_SIZE_BOTH_TYPES];

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

int SSD1306_init(int scl, int sda, int cs, int dc, int rst)
{
  _SCL = scl;
  _SDA = sda;
  _CS = cs;
  _DC = dc;
  _RST = rst;
  _Auto = 0;
  
  if (DSIZE == TYPE_128X32)
  {
    _Width = SSD1306_LCDWIDTH;
    _Height = SSD1306_LCDHEIGHT32;
  }
  else
  {
    _Width = SSD1306_LCDWIDTH;
    _Height = SSD1306_LCDHEIGHT64;
  }
  
  //reset display
  high(_RST);
  pause(10);
  low(_RST);
  pause(10);
  high(_RST);

  SSD1306_cmd(SSD1306_DISPLAYOFF);
  SSD1306_cmd(SSD1306_SETDISPLAYCLOCKDIV);
  SSD1306_cmd(0x80);
  
  SSD1306_cmd(SSD1306_SETMULTIPLEX);
  SSD1306_cmd(_Height - 1);

  SSD1306_cmd(SSD1306_SETDISPLAYOFFSET);
  SSD1306_cmd(0x0);
  SSD1306_cmd(SSD1306_SETSTARTLINE);
  SSD1306_cmd(SSD1306_CHARGEPUMP);
  if (CHRGPUMP == SSD1306_EXTERNALVCC)
    SSD1306_cmd(0x10);  //Charge pump off
  else
    SSD1306_cmd(0x14);  //Charge pump on
  SSD1306_cmd(SSD1306_MEMORYMODE);
  SSD1306_cmd(0x00);
  SSD1306_cmd(SSD1306_SEGREMAP | 0x1);
  SSD1306_cmd(SSD1306_COMSCANDEC);
  
  if (DSIZE == TYPE_128X32)
  {
    SSD1306_cmd(SSD1306_SETCOMPINS);
    SSD1306_cmd(0x02);
    SSD1306_cmd(SSD1306_SETCONTRAST);
    SSD1306_cmd(0x8F);
  }    
  
  if (DSIZE == TYPE_128X64)
  {
    SSD1306_cmd(SSD1306_SETCOMPINS);
    SSD1306_cmd(0x12);
    SSD1306_cmd(SSD1306_SETCONTRAST);
    if (CHRGPUMP == SSD1306_EXTERNALVCC)
      SSD1306_cmd(0x9F);
    else
      SSD1306_cmd(0xCF);
  }
  
  SSD1306_cmd(SSD1306_SETPRECHARGE);
  if (CHRGPUMP == SSD1306_EXTERNALVCC)
    SSD1306_cmd(0x22);
  else
    SSD1306_cmd(0xF1);
  SSD1306_cmd(SSD1306_SETVCOMDETECT);
  SSD1306_cmd(0x40);
  SSD1306_cmd(SSD1306_DISPLAYALLON_RESUME);
  SSD1306_cmd(SSD1306_NORMALDISPLAY);
  SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
  SSD1306_cmd(SSD1306_DISPLAYON);
  SSD1306_invert(0);
  SSD1306_cls();
}

void SSD1306_write(char b)
{
  low(_CS);
  shift_out(_SDA, _SCL, MSBFIRST, 8, b);
  high(_CS);
}

void SSD1306_cmd(char c)
{
  low(_DC);
  SSD1306_write(c);
  high(_DC);
}

void SSD1306_invert(int i)
{
  if (i)
    SSD1306_cmd(SSD1306_INVERTDISPLAY);
  else
    SSD1306_cmd(SSD1306_NORMALDISPLAY);
}

void SSD1306_auto(int a)
{
  _Auto = a;
}

void SSD1306_update()
{
  int k;
  
  SSD1306_cmd(SSD1306_SETLOWCOLUMN);
  SSD1306_cmd(SSD1306_SETHIGHCOLUMN);
  SSD1306_cmd(SSD1306_SETSTARTLINE);
  
  k = 0;
  low(_CS);
  while (k < 1024)
  {
    shift_out(_SDA, _SCL, MSBFIRST, 8, _Buffer[k++]);
  }
  high(_CS);  
}
  
void SSD1306_cls()
{
  memset(&_Buffer, 0, sizeof(_Buffer));
  SSD1306_cmd(SSD1306_DISPLAYOFF);
  SSD1306_update();
  SSD1306_cmd(SSD1306_DISPLAYON);
}

char* SSD1306_getBuffer()
{
  return _Buffer;
}

void SSD1306_scrollRight(char sp, char ep, char f)
{
  SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
  SSD1306_cmd(SSD1306_RIGHT_HORIZ_SCROLL);
  SSD1306_cmd(0x00); // Dummy
  SSD1306_cmd(sp & 0x07);
  SSD1306_cmd(f & 0x07);
  SSD1306_cmd(ep & 0x07);
  SSD1306_cmd(0x00);
  SSD1306_cmd(0xFF);
  SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}

void SSD1306_scrollLeft(char sp, char ep, char f)
{
  SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
  SSD1306_cmd(SSD1306_LEFT_HORIZ_SCROLL);
  SSD1306_cmd(0x00); // Dummy
  SSD1306_cmd(sp & 0x07);
  SSD1306_cmd(f & 0x07);
  SSD1306_cmd(ep & 0x07);
  SSD1306_cmd(0x00);
  SSD1306_cmd(0xFF);
  SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}

void SSD1306_scrollDiagRight(char sp, char ep, char f)
{
  SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
  SSD1306_cmd(SSD1306_VERTRIGHTHORIZSCROLL);
  SSD1306_cmd(0x00); // Dummy
  SSD1306_cmd(sp & 0x07);
  SSD1306_cmd(f & 0x07);
  SSD1306_cmd(ep);
  SSD1306_cmd(0x01);
  SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}

void SSD1306_scrollDiagLeft(char sp, char ep, char f)
{
  SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
  SSD1306_cmd(SSD1306_VERTLEFTHORIZSCROLL);
  SSD1306_cmd(0x00); // Dummy
  SSD1306_cmd(sp & 0x07);
  SSD1306_cmd(f & 0x07);
  SSD1306_cmd(ep & 0x07);
  SSD1306_cmd(0x01);
  SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}

void SSD1306_scrollStop()
{
  SSD1306_cmd(SSD1306_DEACTIVATE_SCROLL);
}

void SSD1306_plot(short x, short y, char z)
{
  int i;
  char r, p;
  
  if (x >= _Width)
    return;
  if (y >= _Height)
    return;

  i = y / 8 * 128;
  r = y % 8;
  r = 1 << r;
  p = _Buffer[i+x];
  if (z)
    _Buffer[i+x] = p | r;
  else
    _Buffer[i+x] = p & ~r;
}

void SSD1306_writeChar(char x, char y, char ch)
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
      SSD1306_plot(x+j, y+i, (v & 0x01));
      v = v >> 2;
    }
  }    
}

void SSD1306_writeStr(char x, char y, char *c)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 16) && (c[i] > 0))
  {
    v = c[i++];
    SSD1306_writeChar(x, y, v);
    if (i == 8)
    {
      y = y + 32;
      x = x1;
    }
    else
      x = x + 16;
  }
  if (_Auto)
    SSD1306_update();
}

void SSD1306_writeSChar(char x, char y, char c)
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
        SSD1306_plot(x+j, y, (v & 0x01));
        v = v >> 1;
      }
      y++;
    }
  }
}

void SSD1306_writeSStr(char x, char y, char *c)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 32) && (c[i] > 0))
  {
    v = c[i++];
    SSD1306_writeSChar(x, y, v);
    if (i == 16)
    {
      y = y + 8;
      x = x1;
    }
    else
      x = x + 8;
  }
  if (_Auto)
    SSD1306_update();
}

void SSD1306_drawLine(short x0, short y0, short x1, short y1, char c)
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
    drawLine(x0, y0, x1, y1, 1);
    return;
  }
  D = 2 * dy - dx;
  y = y0;
  
  for (x = x0;x <= x1;x++)
  {
    SSD1306_plot(x, y, c);
    if (D > 0)
    {
      y = y + z;
      D = D - 2 * dx;
    }
    D = D + 2 * dy;
  }          
  if (_Auto)
    SSD1306_update();
}

void drawLine(short x0, short y0, short x1, short y1, char c)
{
  short dx, dy, D, x, y, z;
  
  dy = y1 - y0;
  if (dy < 0)
  {
    y = y0;y0 = y1;y1 = y;
    x = x0;x0 = x1;x1 = x;
  }
  dy = abs(dy);
  dx = x1 - x0;
  if (dx < 0)
    z = -1;
  else
    z = 1;
  dx = abs(dx);
  D = 2 * dx - dy;
  x = x0;
  
  for (y = y0;y <= y1;y++)
  {
    SSD1306_plot(x, y, c);
    if (D > 0)
    {
      x = x + z;
      D = D - 2 * dy;
    }
    D = D + 2 * dx;
  }
  if (_Auto)
    SSD1306_update();
}

void SSD1306_drawBox(short x0, short y0, short x1, short y1, char c)
{
  SSD1306_drawLine(x0, y0, x1, y0, c);
  SSD1306_drawLine(x0, y0, x0, y1, c);
  SSD1306_drawLine(x1, y0, x1, y1, c);
  SSD1306_drawLine(x0, y1, x1, y1, c);
}
  
void SSD1306_setContrast(short c)
{
  SSD1306_cmd(SSD1306_SETCONTRAST);
  SSD1306_cmd(c);
}
