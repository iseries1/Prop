/**
 * @file mdd3a.h
 * @brief Dual Channel Motor Driver
 * @author Michael Burmeister
 * @date February 19, 2023
 * @version 1.0
 * 
*/

/**
 * @brief Initalize driver
 * @param M1A
 * @param M1B
 * @param M2A
 * @param M2B
 */
void mdd3a_Init(int M1A, int M1B, int M2A, int M2B);


/**
 * @brief Set motor PWM value 1000 - 2000
 * @param motor1
 * @param motor2
 */
void mdd3a_SetPWM(int motor1, int motor2);

/**
 * @brief Shutdown motor driver
 */
void mdd3a_Stop(void);
