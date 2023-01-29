/**
 * @file mc33926.h
 * @brief Driver logic for MC33926 motor drive
 * @author Michael Burmeister
 * @date June 28, 2019
 * @version 1.0
 * 
*/

/**
 * @brief init MC33926 driver
 * @param lin1 left drive 1
 * @param lin2 left drive 2
 * @param lpwm left pulse
 * @param rin1 right drive 1
 * @param rin2 right drive 2
 * @param rpwm right pulse
 */
void mc33926_init(char lin1, char lin2, char lpwm, char rin1, char rin2, char rpwm);

/**
 * @brief set pwm value 1000-2000
 * @param motor1 pwm for motor one 1500 stop 
 * @param motor2 pwm for motor two 1500 stop
 */
void mc33926_setPWM(int motor1, int motor2);

/**
 * @brief stop motor driver
 */
void mc33926_stop(void);
