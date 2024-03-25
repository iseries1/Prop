/**
 * @brief Real Time Clock Driver
 * @author Michael Burmeister
 * @date April 17, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initalize Driver
 * @param clk clock pin
 * @param dta data pin
 * @return status 0 - found
 */
int PCF8523_Init(int clk, int dta);

/**
 * @brief Get Seconds
 * @return seconds
 */
int PCF8523_Seconds(void);

/**
 * @brief Get Minutes
 * @return minutes
 */
int PCF8523_Minutes(void);

/**
 * @brief Get Hour
 * @return hours
 */
int PCF8523_Hour(void);

/**
 * @brief Get Day of Week
 * @return day 0 - 6
 */
int PCF8523_DayofWeek(void);

/**
 * @brief Get Day
 * @return day number
 */
int PCF8523_Day(void);

/**
 * @brief Get Month
 * @return month number
 */
int PCF8523_Month(void);

/**
 * @brief Get Year
 * @return year number + 2000
 */
int PCF8523_Year(void);

/**
 * @brief Set Date
 * @param month 1 - 12
 * @param day 1 - 31
 * @param year 2000 - 2099
 */
void PCF8523_SetDate(int month, int day, int year);

/**
 * @brief Set Time
 * @param hour
 * @param minute
 * @param second
 */
void PCF8523_SetTime(int hours, int minutes, int seconds);

/**
 * @brief Set Date and Time
 * @return serial date value
 */
int PCF8523_SetDateTime(void);

/**
 * @brief Read Control
 * @return control 1, 2, and 3
 */
int PCF8523_Control(void);

/**
 * @brief Set Control
 * @param control 1, 2, and 3 little indian
 */
void PCF8523_SetControl(int control);

/**
 * @brief Set Alarm values
 * @param minutes -1 to skip
 * @param hour -1 to skip
 * @param day -1 to skip
 * @param day of week -1 to skip
 */
void PCF8523_SetAlarm(int minutes, int hours, int day, int dayofweek);

/**
 * @brief Get Alarm values
 * @return value minutes, hour, day, weekday
 */
int PCF8523_GetAlarm(void);

/**
 * @brief Set offset
 * @param offset 0 to disable
 */
void PCF8523_SetOffset(int offset);
