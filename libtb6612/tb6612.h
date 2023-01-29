/**
 * @file tb6612.h
 * @brief Motor Driver for Adafruit TB6612
 * @author Michael Burmeister
 * @date May 3, 2020
 * @version 1.0
 * 
*/


/**
 * @brief Initialize TB6612 driver
 * @param ain1 input 1 A side
 * @param ain2 input 2 A side
 * @param pwma pwm pulse A side
 * @param bin1 input 1 B side
 * @param bin2 input 2 B side
 * @param pwmb pwm pulse B side
 */
void tb6612_init(int ain1, int ain2, int pwma, int bin1, int bin2, int pwmb);

/**
 * @brief Set Motor A and Motor B speed
 * @param motora pwm value for motor a 1500 stop 1000 full reverse 2000 full forward
 * @param motorb pwm value for motor b 1500 stop 1000 full reverse 2000 full forward
 */
void tb6612_setPWM(int motora, int motorb);

/**
 * @brief stop motor driver
 */
void tb6612_shutdown(void);
