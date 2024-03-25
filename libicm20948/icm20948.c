/**
 * @brief ICM20948 9Dof sensor driver
 * @author Michael Burmeister
 * @date February 20, 2023
 * @version 1.0
 * 
*/

#include "simpletools.h"
#include "icm20948_reg.h"
#include "icm20948.h"
#include "i2c.h"

#define ICM_DEV_WHO_AM_I  0xEA
#define ICM_ADDRESS_LOW   0x68
#define ICM_ADDRESS_HIGH  0x69
#define ICM_ADDRESS_MAG   0x0C

int icm_addr;
int mag_addr;
i2c icm;
char _Buffer[12];

int ICM20948_Init(int icmclk, int icmdta)
{
    int i;

    icm_addr = ICM_ADDRESS_HIGH;
    mag_addr = ICM_ADDRESS_MAG;

    i2c_open(&icm, icmclk, icmdta, 0);
    
    _Buffer[0]=255;
    
    i = i2c_in(&icm, icm_addr, ICM_WHO_AM_I, 1, _Buffer, 1);

    if (_Buffer[0] != ICM_DEV_WHO_AM_I)
        return -1;
    
    ICM20948_Reset();
    ICM20948_Sleep(0);
    ICM20948_EnableLowPower(0); // full power
    ICM20948_I2CMaster(0);
    ICM20948_DMP(0);
    ICM20948_FIFO(0);
    pause(1000);
    return 0;
}

void ICM20948_FifoMode(int mode)
{
    int i;

    _Buffer[0] = mode;

    i = i2c_out(&icm, icm_addr, ICM_FIFO_MODE, 1, _Buffer, 1);
}

void ICM20948_DMP(int enable)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0x7f;
    
    if (enable)
        _Buffer[0] = _Buffer[0] | 0x80;
    
    i = i2c_out(&icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
}

void ICM20948_FIFO(int enable)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0xbf;

    if (enable)
        _Buffer[0] = _Buffer[0] | 0x40;
    
    i = i2c_out(&icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
}

void ICM20948_SetFifoData(int data)
{
    int i;

    _Buffer[0] = data >> 8;
    _Buffer[1] = data;

    i = i2c_out(&icm, icm_addr, ICM_FIFO_EN_1, 1, _Buffer, 2);
}

short ICM20948_FifoCount(void)
{
    int i;
    short v;

    i = i2c_in(&icm, icm_addr, ICM_FIFO_COUNT, 1, _Buffer, 2);

    v = _Buffer[0] << 8 | _Buffer[1];

    return v;
}

short ICM20948_ReadFifo(int count, char *buffer)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_FIFO_RW, 1, buffer, count);

    return i;
}

void ICM20948_I2CMaster(int enable)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
    if (enable)
        _Buffer[0] = _Buffer[0] | 0x20;
    else
        _Buffer[0] = _Buffer[0] & 0xdf;
    
    i = i2c_out(&icm, icm_addr, ICM_USER_CTRL, 1, _Buffer, 1);
}

void ICM20948_Reset()
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] | 0x80;

    i = i2c_out(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
    pause(500);
}

void ICM20948_Sleep(int mode)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0x3f;
    if (mode)
        _Buffer[0] = _Buffer[0] | 0x40;
    
    i = i2c_out(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
    pause(100);
}

void ICM20948_EnableLowPower(int mode)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0xdf;
    if (mode)
        _Buffer[0] = _Buffer[0] | 0x20;
    
    i = i2c_out(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
}

void ICM20948_SetClock(int source)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);

    _Buffer[0] = _Buffer[0] & 0xf8;
    _Buffer[0] = _Buffer[0] | (source & 0x07);
    
    i = i2c_out(&icm, icm_addr, ICM_PWR_MGMT_1, 1, _Buffer, 1);
}

int ICM20948_Interupts(void)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_INT_STATUS, 1, _Buffer, 4);

    i = _Buffer[0];
    return i;
}

void ICM20948_ByPass(int mode)
{
    int i;

    _Buffer[0] = mode << 1;

    i = i2c_out(&icm, icm_addr, ICM_INT_PIN_CFG, 1, _Buffer, 1);
}

int ICM20948_Delay(void)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_DELAY_TIME, 1, _Buffer, 2);

    i = _Buffer[0] << 8 | _Buffer[1];

    return i;
}

int ICM20948_DataReady(void)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_DATA_RDY, 1, _Buffer, 1);

    i = _Buffer[0] &0x03;

    return i;
}

void ICM20948_Accel(short *x, short *y, short *z)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_ACCEL_XOUT, 1, _Buffer, 6);

    *x = _Buffer[0] << 8 | _Buffer[1];
    *y = _Buffer[2] << 8 | _Buffer[3];
    *z = _Buffer[4] << 8 | _Buffer[5];

}

void ICM20948_Gyro(short *x, short *y, short *z)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_GYRO_XOUT, 1, _Buffer, 6);

    *x = _Buffer[0] << 8 | _Buffer[1];
    *y = _Buffer[2] << 8 | _Buffer[3];
    *z = _Buffer[4] << 8 | _Buffer[5];

}

int ICM20948_Temp(void)
{
    int i;

    i = i2c_in(&icm, icm_addr, ICM_TEMP_OUT, 1, _Buffer, 2);

    i = _Buffer[0] << 8 | _Buffer[1];

    return i;
}

void ICM20948_ResetFifo(void)
{
    int i;

    _Buffer[0] = 0x1f;
    i = i2c_out(&icm, icm_addr, ICM_FIFO_RST, 1, _Buffer, 1);

    _Buffer[0] = 0x1e;
    i = i2c_out(&icm, icm_addr, ICM_FIFO_RST, 1, _Buffer, 1);
}

void ICM20948_ConfigGyro(int filter, int range, int enable)
{
    int i;

    ICM20948_SetBank(2);

    _Buffer[0] = filter << 3 | range << 1 | enable;

    i = i2c_out(&icm, icm_addr, ICM_GYRO_CONFIG, 1, _Buffer, 1);
}

void ICM20948_GyroOffsets(short *x, short *y, short *z)
{
    int i;

    ICM20948_SetBank(2);

    i = i2c_in(&icm, icm_addr, ICM_GYRO_OFFSET, 1, _Buffer, 6);

    *x = _Buffer[0] << 8 | _Buffer[1];
    *y = _Buffer[2] << 8 | _Buffer[3];
    *z = _Buffer[4] << 8 | _Buffer[5];

    ICM20948_SetBank(0);
}

void ICM20948_SetGyroOffsets(short x, short y, short z)
{
    int i;

    ICM20948_SetBank(2);

    _Buffer[0] = x >> 8;
    _Buffer[1] = x;
    _Buffer[2] = y >> 8;
    _Buffer[3] = y;
    _Buffer[4] = z >> 8;
    _Buffer[5] = z;

    i = i2c_out(&icm, icm_addr, ICM_GYRO_OFFSET, 1, _Buffer, 6);

    ICM20948_SetBank(0);
}

void ICM20948_ConfigAccel(int filter, int range, int enable)
{
    int i;

    ICM20948_SetBank(2);

    _Buffer[0] = filter << 3 | range << 1 | enable;

    i = i2c_out(&icm, icm_addr, ICM_ACCEL_CONFIG, 1, _Buffer, 1);
}

void ICM20948_AccelOffsets(short *x, short *y, short *z)
{
    int i;

    ICM20948_SetBank(1);

    i = i2c_in(&icm, icm_addr, ICM_ACCEL_OFFSETX, 1, _Buffer, 2);
    i = i2c_in(&icm, icm_addr, ICM_ACCEL_OFFSETY, 1, &_Buffer[2], 2);
    i = i2c_in(&icm, icm_addr, ICM_ACCEL_OFFSETZ, 1, &_Buffer[4], 2);

    *x = _Buffer[0] << 8 | _Buffer[1];
    *y = _Buffer[2] << 8 | _Buffer[3];
    *z = _Buffer[4] << 8 | _Buffer[5];

    ICM20948_SetBank(0);
}

void ICM20948_SetAccelOffsets(short x, short y, short z)
{
    int i;

    ICM20948_SetBank(1);

    _Buffer[0] = x >> 8;
    _Buffer[1] = x;
    _Buffer[2] = y >> 8;
    _Buffer[3] = y;
    _Buffer[4] = z >> 8;
    _Buffer[5] = z;

    i = i2c_out(&icm, icm_addr, ICM_ACCEL_OFFSETX, 1, _Buffer, 2);
    i = i2c_out(&icm, icm_addr, ICM_ACCEL_OFFSETY, 1, &_Buffer[2], 2);
    i = i2c_out(&icm, icm_addr, ICM_ACCEL_OFFSETZ, 1, &_Buffer[4], 2);

    ICM20948_SetBank(0);
}

int ICM20948_MagWhoAmI(void)
{
    int i;

    _Buffer[0] = 0;
    i = i2c_in(&icm, mag_addr, ICM_MAG_ID, 1, _Buffer, 1);

    i = _Buffer[0];
    return i;
}

int ICM20948_Mag(short *x, short *y, short *z)
{
    int i;

    i = i2c_in(&icm, mag_addr, ICM_MAG_XOUT, 1, _Buffer, 6);

    *x = _Buffer[1] << 8 | _Buffer[0];
    *y = _Buffer[3] << 8 | _Buffer[2];
    *z = _Buffer[5] << 8 | _Buffer[4];

    i = i2c_in(&icm, mag_addr, ICM_MAG_STATUS2, 1, _Buffer, 1);
    i = (_Buffer[0] & 0x08) >> 3;

    return i;
}

int ICM20948_MagCtrl(void)
{
    int i;

    i = i2c_in(&icm, mag_addr, ICM_MAG_CTRL2, 1, _Buffer, 1);

    i = _Buffer[0];
    return i;
}

void ICM20948_MagMode(int mode)
{
    int i;

    _Buffer[0] = mode;
    i = i2c_out(&icm, mag_addr, ICM_MAG_CTRL2, 1, _Buffer, 1);
}

void ICM20948_SetBank(int bank)
{
    int i;

    _Buffer[0] = bank << 4;

    i = i2c_out(&icm, icm_addr, ICM_BANK_SELECT, 1, _Buffer, 1);
}

void ICM20948_WriteMemory(short addr, char *data)
{
    int i;

    _Buffer[0] = addr;
    i = i2c_out(&icm, icm_addr, ICM_MEM_START, 1, _Buffer, 1);

    i = i2c_out(&icm, icm_addr, ICM_MEM_RW, 1, data, 16);
}

void ICM20948_ReadMemory(short addr, char *data)
{
    int i;

    _Buffer[0] = addr;
    i = i2c_out(&icm, icm_addr, ICM_MEM_START, 1, _Buffer, 1);

    i = i2c_in(&icm, icm_addr, ICM_MEM_RW, 1, data, 16);
}
