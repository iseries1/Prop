/**
 * @file ssd1306reg.h
 * @brief SSD1306 Command values
 * @author Michael Burmeister
 * @date March 14, 2018
 * @version 1.0
 */

#define CHRGPUMP 2
#define DSIZE 64
#define BLACK 0
#define WHITE 1

#define TYPE_128X32 32
#define TYPE_128X64 64
#define LCD_BUFFER_SIZE_BOTH_TYPES 1024
#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT32 32
#define SSD1306_LCDHEIGHT64 64
#define SSD1306_LCDCHARMAX 8

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

//Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERT_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZ_SCROLL 0x26
#define SSD1306_LEFT_HORIZ_SCROLL 0x27
#define SSD1306_VERTRIGHTHORIZSCROLL 0x29
#define SSD1306_VERTLEFTHORIZSCROLL 0x2A

#ifndef ENDEF
#define ENDEF
enum
{
  Frame5,
  Frame64,
  Frame128,
  Frame256,
  Frame3,
  Frame4,
  Frame25,
  Frame2
};

#endif
