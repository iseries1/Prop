/**
 * @file stepper.h
 * @brief Stepper Motor Driver logic
 * @author Michael Burmeister
 * @date March 14, 2019
 * @version 1.0
 * 
*/

/**
 * @brief setup stepper logic
 * @param enableA
 * @param directionA
 * @param stepA
 * @param enableB
 * @param directionB
 * @param stepB
 */
void Stepper_init(char enableA, char directionA, char stepA, char enableB, char directionB, char stepB);

/**
 * @brief enable motors
 * @param enable
 */
void Stepper_enable(char enable);

/**
 * @brief single step
 * @param motorA
 * @param motorB
 */
void Stepper_single(char motorA, char motorB);

/**
 * @brief set direction of turn
 * @param directionA 1 = clock wise, 2 = counter clock wise
 * @param directionB 1 = clock wise, 2 = counter clock wise
 */
void Stepper_direction(char directionA, char directionB);

/**
 * @brief step stepper speed of turn
 * @param speedA
 * @param speedB
 */
void Stepper_speed(short speedA, short speedB);
