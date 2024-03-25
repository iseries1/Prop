/**
 * @file tsl2591.h
 * @brief Driver for TSL2591 Light Sensor
 * @author Michael Burmeister
 * @date April 15, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Setup connection to device
 * @param clk clock pin
 * @param dta data pin
 * @return id
 */
int TSL2591_Init(int clk, int dta);

/**
 * @brief Get device ID
 * @return id of device (0x50)
 */
int TSL2591_GetID(void);

/**
 * @brief Get Status
 * @return status
 */
int TSL2591_GetStatus(void);

/**
 * @brief Read light levels
 * @param ch0 address for channel 0
 * @param ch1 address for channel 1
 */
int TSL2591_Read(int *ch0, int *ch1);

/**
 * @brief Reset device
 */
void TSL2591_Reset(void);

/**
 * @brief Enable Unit
 * @param state 0 - power down, 1 - power up
 */
void TSL2591_Enable(int state);

/**
 * @bief Set Gain Value
 * @param gain 0 - low, 1 - medium, 2 - high, 3 - maxium
 */
void TSL2591_SetGain(int gain);

/**
 * @brief Set Integration Time
 * @param time 0 - 100ms, 1 - 200ms, 2 - 300ms, 3 - 400ms, 4 - 500ms, 5 - 600ms
 */
void TSL2591_SetIntegration(int time);
