/**
 * @brief BME680 Environmental Sensor
 * @author Michael Burmeister
 * @date December 7, 2019
 * @version 1.0
 * 
*/

#define BME680_I2C_ADDR_PRIMARY 0x76
#define BME680_I2C_ADDR_SECONDARY  0x77

#define BME680_CHIP_ID 0x61

#define BME680_COEFF_SIZE 41
#define BME680_COEFF_ADDR1_LEN 25
#define BME680_COEFF_ADDR2_LEN 16

#define BME680_FIELD_LENGTH 0x15
#define BME680_FIELD_ADDR_OFFSET 0x17

#define BME680_SOFT_RESET_CMD 0xb6

#define BME680_I_MIN_CORRECTION 0x01
#define BME680_I_MAX_CORRECTION 0x02

/** Register map */
#define BME680_ADDR_RES_HEAT_VAL_ADDR 0x00
#define BME680_ADDR_RES_HEAT_RANGE_ADDR 0x02
#define BME680_ADDR_RANGE_SW_ERR_ADDR 0x04
#define BME680_ADDR_SENS_CONF_START 0x5a
#define BME680_ADDR_GAS_CONF_START 0x64

#define BME680_FIELD0_ADDR 0x1d
#define BME680_RES_HEAT0_ADDR 0x5a
#define BME680_GAS_WAIT0_ADDR 0x64

#define BME680_CONF_HEAT_CTRL_ADDR 0x70
#define BME680_CONF_ODR_RUN_GAS_NBC_ADDR 0x71
#define BME680_CONF_OS_H_ADDR 0x72
#define BME680_MEM_PAGE_ADDR 0xf3
#define BME680_CONF_T_P_MODE_ADDR 0x74
#define BME680_CONF_ODR_FILT_ADDR 0x75

#define BME680_COEFF_ADDR1 0x89
#define BME680_COEFF_ADDR2 0xe1

#define BME680_CHIP_ID_ADDR 0xd0
#define BME680_SOFT_RESET_ADDR 0xe0

#define BME680_ENABLE_HEATER 0x00
#define BME680_DISABLE_HEATER 0x01

#define BME680_DISABLE_GAS_MEAS 0x00
#define BME680_ENABLE_GAS_MEAS 0x01

#define BME680_OS_NONE 0x00
#define BME680_OS_1X 0x01
#define BME680_OS_2X 0x02
#define BME680_OS_4X 0x03
#define BME680_OS_8X 0x04
#define BME680_OS_16X 0x05

#define BME680_FILTER_SIZE_0 0x00
#define BME680_FILTER_SIZE_1 0x01
#define BME680_FILTER_SIZE_3 0x02
#define BME680_FILTER_SIZE_7 0x03
#define BME680_FILTER_SIZE_15 0x04
#define BME680_FILTER_SIZE_31 0x05
#define BME680_FILTER_SIZE_63 0x06
#define BME680_FILTER_SIZE_127 0x07

#define BME680_SLEEP_MODE 0x00
#define BME680_FORCED_MODE 0x01

#define BME680_RESET_PERIOD 0x0a

#define BME680_MEM_PAGE0 0x10
#define BME680_MEM_PAGE1 0x00

#define BME680_HUM_REG_SHIFT_VAL 0x04

#define BME680_RUN_GAS_DISABLE 0x00
#define BME680_RUN_GAS_ENABLE 0x01

#define BME680_TMP_BUFFER_LENGTH 40
#define BME680_REG_BUFFER_LENGTH 6
#define BME680_FIELD_DATA_LENGTH 3
#define BME680_GAS_REG_BUF_LENGTH 20

#define BME680_OST_SEL 1
#define BME680_OSP_SEL 2
#define BME680_OSH_SEL 4
#define BME680_GAS_MEAS_SEL 8
#define BME680_FILTER_SEL 16
#define BME680_HCNTRL_SEL 32
#define BME680_RUN_GAS_SEL 64
#define BME680_NBCONV_SEL 128
#define BME680_GAS_SENSOR_SEL (BME680_GAS_MEAS_SEL | BME680_RUN_GAS_SEL | BME680_NBCONV_SEL)

#define BME680_NBCONV_MIN 0
#define BME680_NBCONV_MAX 10
