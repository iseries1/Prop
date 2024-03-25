/**
 * @brief BME680 Environement Sensor Driver
 * @author Michael Burmeister
 * @date March 31, 2023
 * @version 1.0
 * 
*/

//#define BME68X_DO_NOT_USE_FPU

#include "simpletools.h"
#include "bme68x.h"
#include "timer.h"


#define BMCLK 18
#define BMDTA 17

uint8_t BME68xRead(uint8_t, uint8_t *, uint16_t len, void *);
uint8_t BME68xWrite(uint8_t, uint8_t *, uint16_t len, void *);
void BME68xWait(uint32_t, void *);


#define SAMPLE_COUNT  UINT16_C(30)

i2c *Bme;
unsigned long T;
char bmemode;

int main()
{
  int i;
  
  	uint8_t dev_addr;
	uint16_t sample_count = 1;
	uint32_t del_period;

   /* Heater temperature in degree Celsius */
   uint16_t temp_prof[10] = { 100, 100, 200, 200, 200, 200, 320, 320, 320, 320 };

   /* Heating duration in milliseconds */
   uint16_t dur_prof[10] = { 280, 5740, 280, 1960, 1960, 1960, 280, 1960, 1960, 1960 };

	printi("Starting\n");

	Bme = i2c_newbus(BMCLK, BMDTA, 0);

  //bmemode = BME68X_SEQUENTIAL_MODE;
  bmemode = BME68X_FORCED_MODE;
  
	struct bme68x_dev gas_sensor;
	struct bme68x_conf conf;
	struct bme68x_heatr_conf heatr_conf;
	struct bme68x_data data[3];
	uint32_t time_ms = 0;
	uint8_t n_fields;
	int ct;

	dev_addr = BME68X_I2C_ADDR_HIGH;
	gas_sensor.variant_id = BME68X_VARIANT_GAS_LOW;
	gas_sensor.intf = BME68X_I2C_INTF;
	gas_sensor.read = BME68xRead;
	gas_sensor.write = BME68xWrite;
	gas_sensor.delay_us = BME68xWait;
	gas_sensor.amb_temp = 20;
	gas_sensor.intf_ptr = &dev_addr;
	
	int8_t rslt = BME68X_OK;
	rslt = bme68x_init(&gas_sensor);
	
 	printi("Results: %d\n", rslt);
 	
 	uint8_t set_required_settings;
 	/* Set the temperature, pressure and humidity settings */
 	conf.os_hum = BME68X_OS_16X;
 	conf.os_pres = BME68X_OS_1X;
 	conf.os_temp = BME68X_OS_2X;
 	conf.filter = BME68X_FILTER_SIZE_15;
	conf.odr = BME68X_ODR_NONE;
 	rslt = bme68x_set_conf(&conf, &gas_sensor);

 	/* Set the remaining gas sensor settings and link the heating profile */
	heatr_conf.enable = BME68X_ENABLE;

 	/* Create a ramp heat waveform in 3 steps */
   heatr_conf.heatr_temp = 300; /* degree Celsius */
   heatr_conf.heatr_dur = 100; /* milliseconds */
   heatr_conf.heatr_temp_prof = temp_prof;
   heatr_conf.heatr_dur_prof = dur_prof;
   heatr_conf.profile_len = 10;

	rslt = bme68x_set_heatr_conf(bmemode, &heatr_conf, &gas_sensor);
	
 	printi("Config Results: %d\n", rslt);
	
    /* Trigger the next measurement if you would like to read data out continuously */
	rslt = bme68x_set_op_mode(bmemode, &gas_sensor);

	printi("Sample, TimeStamp(ms), Temp(deg C), Pressure(Pa), Humidity(%%), Gas resistance(ohm), Status, Gas Index, Index\n");

	ct = millis(&T);
 	while(sample_count < SAMPLE_COUNT)
 	{
 	    /* Trigger the next measurement if you would like to read data out continuously */
     if (bmemode == BME68X_FORCED_MODE)
        rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, &gas_sensor);

		del_period = bme68x_get_meas_dur(bmemode, &conf, &gas_sensor) + (heatr_conf.heatr_dur * 1000);

		gas_sensor.delay_us(del_period, gas_sensor.intf_ptr);

		time_ms = millis(&T);

		rslt = bme68x_get_data(bmemode, &data, &n_fields, &gas_sensor);

		for (int i = 0;i<n_fields;i++)
		{
			print("%6d, %13d, %11.2f, %12.2f, %11.2f, %19d, %6x, %10d, %4d\n",
				sample_count, time_ms, data[i].temperature, data[i].pressure/3386, data[i].humidity, 
				data[i].gas_resistance, data[i].status, data[i].gas_index, data[i].meas_index);

			sample_count++;
		}
 	}
 
  while(1)
  {
    pause(1000);
  }  
}

uint8_t BME68xRead(uint8_t reg_addr, uint8_t *data, uint16_t len, void *intf_ptr)
{
    int i;
    
	uint8_t dev_addr = *(uint8_t*)intf_ptr;

	i = i2c_in(Bme, dev_addr, reg_addr, 1, data, len);

#ifdef DEBUG
	print("Read> i:%d, addr: %x, reg:%x, Len:%d, (%x)", i, dev_addr, reg_addr, len, data[0]);
	for (int j=1;j<len;j++)
		print(", (%x)", data[j]);
	print("\n");
#endif

    if (i > 0)
    	return 0;
    else
    	return -1;
}

uint8_t BME68xWrite(uint8_t reg_addr, uint8_t *data, uint16_t len, void *intf_ptr)
{
    int i;

	uint8_t dev_addr = *(uint8_t*)intf_ptr;

	i = i2c_out(Bme, dev_addr, reg_addr, 1, data, len);
    
#ifdef DEBUG
	print("Write> i:%d, id:%x, reg:%x, len:%d\n", i, dev_addr, reg_addr, len);
#endif

    if (i > 0)
    	return 0;
    else
    	return -1;
}

void BME68xWait(uint32_t period, void *intf_ptr)
{
    usleep(period);
}
