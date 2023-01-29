/**
 * @brief MS5607 pressure drive
 * @author Michael Burmeister
 * @date May 24, 2020
 * @version 1.0
 * 
*/

#define DEVICE_ADDR 0xec
#define CMD_READ_ADC 0x00
#define CMD_RESET 0x1e
#define CMD_CONV_ADC 0x40
#define CMD_READ_PROM 0xa0

#define RSLT_D1 0x00
#define RSLT_D2 0x10


