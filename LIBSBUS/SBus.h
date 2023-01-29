/**
 * @file sbus.h
 * @brief SBus receiver decoder
 * @author Michael Burmeister
 * @date December 13, 2017
 * @version 1.1
 * 
*/

/**
 * @brief Startup cog to read SBus data
 * 
 * @param pin number for SBus device
 */
int SBus_open(char pin);

/**
 * @brief Get SBus Channel value raw
 * 
 * @param c Channel number 1 - 16
 * @return short cog number
 */
short SBus_getChannel(char c);

/**
 * @brief Get Adjust Channel value
 *        trys to scale the value between
 *        1000 and 2000
 * @param c Channel number 1 - 16
 * @return short channel value
 */
short SBus_getAdjChannel(char c);

/**
 * @brief Get status of SBus device
 * 
 * @return short -1 for no radio and 1 for frame lost
 */
short SBus_getStatus(void);

/**
 * @brief get scaled channel between 1000 and 2000 range
 *        this is done by setting the min and max values
 *        for each channel using the setScaledChannel
 * @param channel 1 - 16
 * @return scaled
 */
int SBus_getScaledChannel(char channel);

/**
 * @brief set scaled channel value min and max
 *        by setting these values you can scale
 *        the output between 1000 and 2000
 * @param channel 1 - 16
 * @param min value
 * @param max value
 */
void SBus_setScaledChannel(char channel, int min, int max);
