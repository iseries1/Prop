/**
 * @file ssd1306.h
 * @brief SSD1306 Display driver
 * @author Michael Burmeister
 * @date March 14, 2018
 * @version 1.0
 * 
 */

// Display in use
//#define SSD1306_128_64
//#define SSD1306_128_32
#include "SSD1306Reg.h"

/*
 * @brief Initalize display
 * @param SCL clock line
 * @param SDA data line
 * @param CS chip select
 * @param DC data command select
 * @param RST reset display select
 */
int SSD1306_init(int SCL, int SDA, int CS, int DC, int RST);

/*
 * @brief Send data to display
 * @param b byte to send
 */
void SSD1306_write(char b);

/*
 * @brief Send command to display
 * @param c command to send
 */
void SSD1306_cmd(char c);

/*
 * @brief Invert display
 * @param v value equals true or zero for false
 */
void SSD1306_invert(int v);

/*
 * @brief AutoUpdate
 * @param t turn on or off
 */
void SSD1306_auto(int t);

/*
 * @brief Update display with buffer
 * @param none
 */
void SSD1306_update(void);

/*
 * @brief Clear screen buffer and screen
 */
void SSD1306_cls(void);

/*
 * @brief Return pointer to buffer
 * @return _Buffer
 */
char* SSD1306_getBuffer(void);

/*
 * @brief Scroll right
 * @param starting page
 * @param ending page
 * @param frame speed
 */
void SSD1306_scrollRight(char, char, char);

/*
 * @brief Scroll left
 * @param starting page
 * @param ending page
 * @param frame speed
 */
void SSD1306_scrollLeft(char, char, char);

/*
 * @brief Scroll diagonal right
 * @param starting page
 * @param ending page
 */
void SSD1306_scrollDiagRight(char, char, char);

/*
 * @brief Scroll diagonal left
 * @param starting page
 * @param ending page
 * @param c
 */
void SSD1306_scrollDiagLeft(char starting, char ending, char c);

/*
 * @brief Scroll stop
 */
void SSD1306_scrollStop(void);

/*
 * @brief plot a poiint
 * @param x offset
 * @param y offset
 * @param color on/off
 */
void SSD1306_plot(short x, short y, char color);

/*
 * @brief write char
 * @param x offset
 * @param y offset
 * @param c character
 */
void SSD1306_writeChar(char x, char y, char c);

/*
 * @brief write string
 * @param x offset
 * @param y offset
 * @param s pointer to string
 */
void SSD1306_writeStr(char x, char y, char* s);

/*
 * @brief write small char
 * @param x offset
 * @param y offset
 * @param c character
 */
void SSD1306_writeSChar(char x, char y, char c);

/*
 * @brief write small string
 * @param x offset
 * @param y offset
 * @param c pointer to string
 */
void SSD1306_writeSStr(char x, char y, char* c);

/*
 * @brief Bresenham's line algorithm
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color On/Off
 */
void SSD1306_drawLine(short x, short y, short x1, short y1, char color);

/*
 * @brief draw a box
 * @param x start point
 * @param y start point
 * @param x1 end point
 * @param y1 end point
 * @param color On/Off
 */
void SSD1306_drawBox(short x, short y, short x1, short y1, char color);

/*
 * @brief set Contrast
 * @param value
 */
void SSD1306_setContrast(short value);

