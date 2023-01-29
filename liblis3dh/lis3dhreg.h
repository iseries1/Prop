/**
 * @brief Device Driver for LIS3DH
 * @author Michael Burmeister
 * @date May 8, 2020
 * @version 1.0
 * 
*/

#define WHO_AM_I 0x0f
#define STATUS_REG_AUX 0x07
#define OUT_ADC1 0x08
#define OUT_ADC2 0x0a
#define OUT_ADC3 0x0c
#define CTRL_REG0 0x1e
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25
#define REFERENCE 0x26
#define STATUS_REG 0x27
#define TEMP_CFG_REG 0x1f
#define OUT_X 0x28
#define OUT_Y 0x2a
#define OUT_Z 0x2c
#define FIFO_CTRL_REG 0x2e
