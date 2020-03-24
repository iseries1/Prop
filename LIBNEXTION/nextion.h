/**
 * @file nextion.h
 * @brief Interface to Nextion display
 * @author Michael Burmeister
 * @date December 21, 2017
 * @version 1.0
 * @mainpage Custom Libraries
 * <a href="nextion_8h.html">Nextion Display Driver.</a><br>
*/

/**
 * @brief Open connection to display panel
 * @param rx Receive pin
 * @param tx Transmit pin
 * @param baud serial transmit/receive speed
 * @return open status
 */
int Nextion_open(int rx, int tx, int baud);

/**
 * @brief Send Nextion command to panel
 * @param c command string
 */
void Nextion_cmd(char *c);

/**
 * @brief get Nextion display error value
 * @return error
 */
int Nextion_error(void);

/**
 * @brief get Nextion serial number
 * @return character string value
 */
char *Nextion_serialno(void);

/**
 * @brief get page number
 * @return page number
 */
int Nextion_page(void);

/**
 * @brief get numeric value from panel
 * @return integer value
 */
int Nextion_getnumeric(void);

/**
 * @brief get text value from panel
 * @return Character string
 */
char *Nextion_gettext(void);

/**
 * @brief set text value for text object
 * @param var text object variable
 * @param val text string to set
 */ 
void Nextion_settext(char *var, char *val);

/**
 * @brief set numeric value
 * @param var numeric object to set
 * @param val numeric value to set
 */
void Nextion_setnumeric(char *var, int val);

/**
 * @brief set baud rate for panel
 * @param baud baud rate value
 */
void Nextion_setbaud(int baud);

/**
 * @brief close connection to panel
 */
void Nextion_close(void);

/**
 * @brief put panel to sleep
 * @param t seconds to sleep
 */
void Nextion_setsleep(int t);

/**
 * @brief set brightness level of panel
 * @param b brightness level 0 - 100
 */
void Nextion_setbrightness(int b);

/**
 * @brief send string to display
 * @param x x coordinate
 * @param y y coordinate
 * @param w width of the defined area
 * @param h height of the defined area
 * @param f font resource number
 * @param pco foreground color value
 * @param bco background color value
 * @param xcen position of text 0-left, 1-center, 2-right
 * @param ycen position of text 0-top, 1-center, 3-bottom
 * @param sta background fill 0-crop, 1-solid, 2-image, 3-none
 * @param text data to display
 */
void Nextion_xstr(short x, short y, short w, short h, char f, int pco, int bco, char xcen, char ycen, char sta, char *text);

/**
 * @brief send click event 0/1 up/down
 * @param item item name to click
 * @param value 0 or 1 for up or down click
 */
void Nextion_click(char *item, char value);
