/**
 * @brief Temperature Humidity and Pressure sensor
 * @author Michael Burmeister
 * @date April 23, 2022
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "bme280.h"


void print_sensor_data(struct bme280_data *);
int8_t stream_sensor_data_forced_mode(struct bme280_dev *);
int8_t stream_sensor_data_normal_mode(struct bme280_dev *);

BME280_INTF_RET_TYPE bme280Read(uint8_t, uint8_t *, uint16_t, void *);
BME280_INTF_RET_TYPE bme280Write(uint8_t, uint8_t *, uint16_t, void *);
void bme280Wait(uint32_t, void *);


#define BMESCL 7
#define BMESDA 6

static i2c *bme;


int main()
{
  bme = i2c_newbus(BMESCL, BMESDA, 0);

    struct bme280_dev dev;
    int8_t rslt = BME280_OK;
    uint8_t dev_addr = BME280_I2C_ADDR_SEC;
    
    dev.intf_ptr = &dev_addr;
    dev.intf = BME280_I2C_INTF;
    dev.read = (bme280_read_fptr_t)bme280Read;
    dev.write = (bme280_write_fptr_t)bme280Write;
    dev.delay_us = (bme280_delay_us_fptr_t)bme280Wait;
    
    rslt = bme280_init(&dev);

    switch (rslt)
    {
        case 0: printf("Ok\n");
        break;
        case -1: printf("Null Pointer\n");
        break;
        case -2: printf("Device Not Found\n");
        break;
        case -3: printf("Invalid Length\n");
        break;
        case -4: printf("Comunictions Failed\n");
        break;
        case -5: printf("Sleep Mode Failed\n");
        break;
        case -6: printf("Environment Copy Failed\n");
        break;
    }
    
    stream_sensor_data_normal_mode(&dev);

    //stream_sensor_data_forced_mode(&dev);
 
  while(1)
  {
    pause(1000);
    
  }  
}

int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    int8_t rslt;
    uint8_t settings_sel;
	uint32_t req_delay;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    rslt = bme280_set_sensor_settings(settings_sel, dev);
	
	/*Calculate the minimum delay required between consecutive measurement based upon the sensor enabled
     *  and the oversampling configuration. */
    req_delay = bme280_cal_meas_delay(&dev->settings);

    printf("Temperature, Pressure, Humidity\r\n");
    /* Continuously stream sensor data */
    while (1) {
        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        /* Wait for the measurement to complete and print data @25Hz */
        dev->delay_us(req_delay, dev->intf_ptr);
        pause(1000);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        print_sensor_data(&comp_data);
    }
    return rslt;
}

void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature * 9/5+3200, comp_data->pressure, comp_data->humidity);
#else
        printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure/34, comp_data->humidity);
#endif
}

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	printf("Temperature, Pressure, Humidity\r\n");
	while (1) {
		/* Delay while the sensor completes a measurement */
		dev->delay_us(70, dev->intf_ptr);
		pause(1000);
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	}

	return rslt;
}

BME280_INTF_RET_TYPE bme280Read(uint8_t reg_addr, uint8_t *data, uint16_t len, void *dev_id)
{
    int i;
    
    i = *(uint8_t*)dev_id;
    i = i2c_in(bme, i, reg_addr, 1, data, len);

    if (i > 0)
    	return 0;
    else
    	return -1;
}

BME280_INTF_RET_TYPE bme280Write(uint8_t reg_addr, uint8_t *data, uint16_t len, void *dev_id)
{
    int i;

	i = *(uint8_t*)dev_id;
    i = i2c_out(bme, i, reg_addr, 1, data, len);

    if (i > 0)
    	return 0;
    else
    	return -1;
}

void bme280Wait(uint32_t period, void *dev_id)
{
    usleep(period);
}
