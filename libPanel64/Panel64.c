/**
 * @brief Drive Panel 64 LED
 * @author Michael Burmeister
 * @date May 8, 2021
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "panel64.h"

#define PNLAT 7
#define PND 6
#define PNB 5
#define PNE 4
#define PNG2 3
#define PNG1 2
#define PNOE 15
#define PNCLK 14
#define PNC 13
#define PNA 12
#define PNB2 11
#define PNR2 10
#define PNB1 9
#define PNR1 8

void doAddress(int);
void doColor(int, int);
void doRefresh(void*);
void DrawLine(int, int, int, int, int);


char Buffer[64][64];
int ForeGround;
int BackGround;
char *Top, *Bottom;

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

void Panel_Start(void)
{

    ForeGround = 7;
    BackGround = 0;

    memset(Buffer, 0, sizeof(Buffer));

    cog_run(&doRefresh, 50);
}

unsigned int Panel_Color(char red, char green, char blue)
{
    int i;

    i = 0;
    if (red)
        i = 4;
    if (green)
        i = i | 2;
    if (blue)
        i = i | 1;
    
    return i;
}

void Panel_SetPixel(int x, int y, int color)
{
    int i;

    if ((x < 0) || (x > 63))
      return;
    if ((y < 0) || (y > 63))
      return;

    Buffer[y][x] = color;
}

void Panel_TextColor(int foreground, int background)
{
    ForeGround = foreground;
    BackGround = background;
}

void Panel_WriteChar(int x, int y, int character)
{
  long *base;
  int offset;
  long v;
  int x1, y1;

  offset = character & 0xfe;
  base = (long *)0x8000 + (offset << 6);

  if ((x < 0) || (y < 0))
    return;

  offset = 0;
  for (int i=0;i<32;i++)
  {
    v = base[offset++];
    if (character & 0x01)
      v = v >> 1;
  
    for (int j=0;j<16;j++)
    {
      x1 = x + j;
      y1 = y + i;
      if ((v & 0x01) == 1)
        Panel_SetPixel(x1, y1, ForeGround);
      else
        Panel_SetPixel(x1, y1, BackGround);
      v = v >> 2;
    }
  }

}

void Panel_WriteStr(int x, int y, char *string)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 8) && (string[i] > 0))
  {
    v = string[i++];
    Panel_WriteChar(x, y, v);
    if (i == 4)
    {
      y = y + 32;
      x = x1;
    }
    else
      x = x + 16;
  }
}

void Panel_WriteSChar(int x, int y, char character)
{
  char t;
  long v;
  int x1, y1;

  t = character * 2;
  for (int l=0;l<2;l++)
  {
    v = Font_57[t++];
    for (int i=0;i<4;i++)
    {
      for (int j=0;j<8;j++)
      {
        if ((v & 0x01) == 1)
          Panel_SetPixel(x+j, y, ForeGround);
        else
          Panel_SetPixel(x+j, y, BackGround);
        v = v >> 1;
      }
      y++;
    }
  }
}

void Panel_WriteSStr(int x, int y, char *string)
{
  int i, v;
  char x1;
  
  x1 = x;
  i = 0;
  while ((i < 64) && (string[i] > 0))
  {
    v = string[i++];
    Panel_WriteSChar(x, y, v);
    if (i == 10)
    {
      y = y + 8;
      x = x1;
    }
    else
      x = x + 6;
  }
}

void Panel_DrawLine(int x1, int y1, int x2, int y2, int color)
{
  int dx, dy, D, x, y, z;

  dx = x2 - x1;
  if (dx < 0)
    {
      x = x1; x1 = x2; x2 = x;
      y = y1; y1 = y2; y2 = y;
      dx = -dx;
    }

    z = 1;
    dy = y2 - y1;
    if (dy < 0)
    {
      z = -1;
      dy = -dy;
    }

    if (dx < dy)
    {
      DrawLine(x1, y1, x2, y2, color);
      return;
    }

    D = 2 * dy - dx;
    y = y1;

    for (x = x1; x <= x2; x++)
    {
      Panel_SetPixel(x, y, color);
      if (D > 0)
      {
        y = y + z;
        D = D - 2 * dx;
      }
      D = D + 2 * dy;
    }
}

void DrawLine(int x1, int y1, int x2, int y2, int color)
{
  int dx, dy, D, x, y, z;

  dy = y2 - y1;
  if (dy < 0)
  {
    y = y1; y1 = y2; y2 = y;
    x = x1; x1 = x2; x2 = x;
    dy = -dy;
  }

  z = 1;
  dx = x2 - x1;
  if (dx < 0)
  {
    z = -1;
    dx = -dx;
  }

  D = 2 * dx - dy;
  x = x1;

  for (y = y1; y <= y2; y++)
  {
    Panel_SetPixel(x, y, color);
    if (D > 0)
    {
      x = x + z;
      D = D - 2 * dy;
    }
    D = D + 2 * dx;
  }
}

void Panel_DrawBox(int x1, int y1, int x2, int y2, int color)
{
  Panel_DrawLine(x1, y1, x2, y1, color);
  Panel_DrawLine(x1, y1, x1, y2, color);
  Panel_DrawLine(x2, y1, x2, y2, color);
  Panel_DrawLine(x1, y2, x2, y2, color);
}

void Panel_ScrollVertical(int amount)
{
  if (amount > 0)
  {
    for (int i=0;i<64-amount;i++)
    {
      //memcpy(Buffer[i], Buffer[i+amount], 4*64)
      for (int j=0;j<64;j++)
        Buffer[j][i] = Buffer[j][i+amount];
    }

    for (int i=64-amount;i<64;i++)
      for (int j=0;j<64;j++)
        Buffer[j][i] = 0;
  }

  if (amount < 0)
  {
    amount = -amount;
    for (int i=63;i>amount;i--)
    {
      for (int j=0;j<64;j++)
        Buffer[j][i] = Buffer[j][i-1];
    }
    for (int i=amount;i>0;i--)
      for (int j=0;j<64;j++)
        Buffer[j][i] = 0;
  }
}

void Panel_ScrollHorizontal(int amount)
{
  if (amount > 0)
  {
    for (int i=0;i<64-amount;i++)
    {
      //memcpy(Buffer[i], Buffer[i+amount], 4*64)
      for (int j=0;j<64;j++)
        Buffer[i][j] = Buffer[i+amount][j];
    }

    for (int i=64-amount;i<64;i++)
      for (int j=0;j<64;j++)
        Buffer[i][j] = 0;
  }

  if (amount < 0)
  {
    amount = -amount;
    for (int i=63;i>amount;i--)
    {
      for (int j=0;j<64;j++)
        Buffer[i][j] = Buffer[i-1][j];
    }
    for (int i=amount;i>0;i--)
      for (int j=0;j<64;j++)
        Buffer[i][j] = 0;
  }
}

int Panel_GetPixel(int x, int y)
{
  return Buffer[y][x];
}


/*
  low level functions start here
*/

void doRefresh(void *par)
{
  unsigned int t;
  
    //setup pins
    low(PNA);
    low(PNB);
    low(PNC);
    low(PND);
    low(PNE);
    low(PNR1);
    low(PNG1);
    low(PNB1);
    low(PNR2);
    low(PNG2);
    low(PNB2);
    high(PNCLK);
    high(PNOE);
    low(PNLAT);

    while (1)
    {
      t = CNT;
      Top = (char *)Buffer;
      Bottom = &Buffer[32][0];
      
        for (int i=0;i<32;i++)
        {
            for (int j=0;j<64;j++)
            {
              doColor(*Top++, *Bottom++);
                OUTA = OUTA & ~(1 << PNCLK);
                OUTA = OUTA | (1 << PNCLK);
            }
            doAddress(i);
            OUTA = OUTA | (1 << PNLAT);
            OUTA = OUTA & ~(1 << PNLAT);
            OUTA = OUTA & ~(1 << PNOE);
            usleep(20);
            OUTA = OUTA | (1 << PNOE);
        }
	}
}

void doColor(int c1, int c2)
{
  if (c1 & 1)
    OUTA = OUTA | (1 << PNR1);
  else
    OUTA = OUTA & ~(1 << PNR1);

  if (c1 & 2)
    OUTA = OUTA | (1 << PNG1);
  else
    OUTA = OUTA & ~(1 << PNG1);

  if (c1 & 4)
    OUTA = OUTA | (1 << PNB1);
  else
    OUTA = OUTA & ~(1 << PNB1);

  if (c2 & 1)
    OUTA = OUTA | (1 << PNR2);
  else
    OUTA = OUTA & ~(1 << PNR2);

  if (c2 & 2)
    OUTA = OUTA | (1 << PNG2);
  else
    OUTA = OUTA & ~(1 << PNG2);

  if (c2 & 4)
    OUTA = OUTA | (1 << PNB2);
  else
    OUTA = OUTA & ~(1 << PNB2);
}

void doAddress(int a)
{
  
    if (a & 1)
      OUTA = OUTA | (1 << PNA);
    else
      OUTA = OUTA & ~(1 << PNA);

    if (a & 2)
        OUTA = OUTA | (1 << PNB);
    else
        OUTA = OUTA & ~(1 << PNB);

    if (a & 4)
        OUTA = OUTA | (1 << PNC);
    else
        OUTA = OUTA & ~(1 << PNC);

    if (a & 8)
        OUTA = OUTA | (1 << PND);
    else
        OUTA = OUTA & ~(1 << PND);

    if (a & 16)
        OUTA = OUTA | (1 << PNE);
    else
        OUTA = OUTA & ~(1 << PNE);
}
