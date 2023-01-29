/**
 * @brief Driver for MAX7219 7 segment board
 * @author Michael Burmeister
 * @date December 2, 2021
 * @version 1.0
 * 
*/

#define MAX7219_DECODE 0x0900
#define MAX7219_INTENSITY 0x0a00
#define MAX7219_SCANLIMIT 0x0b00
#define MAX7219_SHUTDOWN 0x0c00
#define MAX7219_DISPLAYTEST 0x0f00


/**
 * @brief initilize max7219 driver
 * @param clk clock pin to use
 * @param dta data pin to use
 * @param sel chip select pin
 */
void MAX7219_init(int clk, int dta, int sel);

/**
 * @brief Test all segments
 * @param state 0 - test off 1 - test on
 */
void MAX7219_test(int state);

/**
 * @brief Set number of digets
 * @param digets number of digets from 1 to 8
 */
void MAX7219_digits(int digits);

/**
 * @brief Set display intensity
 * @param percent intensity value 1 - 100%
 */
void MAX7219_intensity(int percent);

/**
 * @brief Set digit value
 * @param digit 7 segment number from 1 to 8
 * @param value 0 - 9 10 - dash, 11 - E, 12 - H, 13 - L, 14 - P, 15 - blank
 * @param decimal decimal point 0 - off, 1 - on
 */
void MAX7219_set(int digit, int value, int decimal);

/**
 * @brief Set Mode
 * @param mask set mode on these digits 0b11111111
 */
void MAX7219_mode(int mask);

/**
 * @brief Shutdown
 * @param onoff 0 - shutdown, 1 - normal
 */
void MAX7219_shutdown(int onoff);

/**
 * @brief print value
 * @param value to print
 * @param decimal position 0 - 8
 */
void MAX7219_print(long value, int decimal);
