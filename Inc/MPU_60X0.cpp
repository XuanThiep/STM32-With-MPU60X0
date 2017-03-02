#include "MPU_60X0.h"


/* Constructor */
MPU60X0::MPU60X0(void)
{
	_hi2c_x = NULL;
}

MPU60X0::MPU60X0(I2C_HandleTypeDef* hi2c_x)
{
	_hi2c_x = hi2c_x;
        Acc_Scale_Factor = 1;
        Gyro_Scale_Factor = 1;
          
}

uint8_t MPU60X0::Who_am_I(void)
{
	uint8_t receive_data;
	HAL_I2C_Mem_Read(_hi2c_x,MPU60X0_ADD<<1,WHO_AM_I,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&receive_data,1,1000);
	return receive_data;
}

void MPU60X0::Initialize(MPU60X0_Accelerometer_t AccelerometerSensitivity,MPU60X0_Gyroscope_t GyroscopeSensitivity)
{
	uint8_t send_data=0;

	/* PLL with X axis gyroscope reference, disabled SLEEP mode, disable CYCLE mode */
	send_data = 0x01;
	HAL_I2C_Mem_Write(_hi2c_x,MPU60X0_ADD<<1,PWR_MGMT_1,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
	HAL_Delay(100);

	/* DLPF enable mode 6 */
	send_data = 0x06;
	HAL_I2C_Mem_Write(_hi2c_x,MPU60X0_ADD<<1,CONFIG,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
	HAL_Delay(100);

        /* Sample rate: 1khz/(0x04+1) = 200Hz */
	send_data = 0x04;
	HAL_I2C_Mem_Write(_hi2c_x,MPU60X0_ADD<<1,SMPLRT_DIV,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
	HAL_Delay(100);
        
        
        /* Set accelerometer scale range */
        HAL_I2C_Mem_Read(_hi2c_x,MPU60X0_ADD<<1,ACCEL_CONFIG,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
        send_data = (send_data & 0xe7)|(AccelerometerSensitivity<<3);
	HAL_I2C_Mem_Write(_hi2c_x,MPU60X0_ADD<<1,ACCEL_CONFIG,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
	HAL_Delay(100);
        
	/* Set gyroscope scale range  */
        HAL_I2C_Mem_Read(_hi2c_x,MPU60X0_ADD<<1,GYRO_CONFIG,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
	send_data = (send_data & 0xe7)|(GyroscopeSensitivity<<3);
	HAL_I2C_Mem_Write(_hi2c_x,MPU60X0_ADD<<1,GYRO_CONFIG,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&send_data,1,1000);
	HAL_Delay(100);

        switch(AccelerometerSensitivity)
        {
        case MPU60X0_Accelerometer_2G:
          Acc_Scale_Factor = MPU60X0_ACCE_SENS_2;
          break;
        case MPU60X0_Accelerometer_4G:
          Acc_Scale_Factor = MPU60X0_ACCE_SENS_4;
          break;
        case MPU60X0_Accelerometer_8G:
          Acc_Scale_Factor = MPU60X0_ACCE_SENS_8;
          break;
        case MPU60X0_Accelerometer_16G:
          Acc_Scale_Factor = MPU60X0_ACCE_SENS_16;
          break;
        }
        
        switch(GyroscopeSensitivity)
        {
        case MPU60X0_Gyroscope_250s:
          Gyro_Scale_Factor = MPU60X0_GYRO_SENS_250;
          break;
        case MPU60X0_Gyroscope_500s:
          Gyro_Scale_Factor = MPU60X0_GYRO_SENS_500;
          break;
        case MPU60X0_Gyroscope_1000s:
          Gyro_Scale_Factor = MPU60X0_GYRO_SENS_1000;
          break;
        case MPU60X0_Gyroscope_2000s:
          Gyro_Scale_Factor = MPU60X0_GYRO_SENS_2000;
          break;
        }
}

void MPU60X0::Get_Gyroscope_value(MPU60X0_Data* Gyroscope_Data)
{
	uint8_t receive_data[6];
        int16_t raw_x,raw_y,raw_z;
        
        HAL_I2C_Mem_Read(_hi2c_x,MPU60X0_ADD<<1,GYRO_XOUT_H,I2C_MEMADD_SIZE_8BIT,receive_data,6,10000);
	raw_x= (int16_t)((receive_data[0]<<8) | receive_data[1]);
	raw_y= (int16_t)((receive_data[2]<<8) | receive_data[3]);
	raw_z= (int16_t)((receive_data[4]<<8) | receive_data[5]);
        
        Gyroscope_Data->x = (float)raw_x/Gyro_Scale_Factor;
        Gyroscope_Data->y = (float)raw_y/Gyro_Scale_Factor;
        Gyroscope_Data->z = (float)raw_z/Gyro_Scale_Factor;
}


void MPU60X0::Get_Accelerometer_value(MPU60X0_Data* Accelerometer_Data)
{
	uint8_t receive_data[6];
        int16_t raw_x,raw_y,raw_z;
        
	HAL_I2C_Mem_Read(_hi2c_x,MPU60X0_ADD<<1,ACCEL_XOUT_H,I2C_MEMADD_SIZE_8BIT,receive_data,6,10000);
	raw_x= (int16_t)((receive_data[0]<<8) | receive_data[1]);
	raw_y= (int16_t)((receive_data[2]<<8) | receive_data[3]);
	raw_z= (int16_t)((receive_data[4]<<8) | receive_data[5]);
        
        Accelerometer_Data->x = (float)raw_x/Acc_Scale_Factor;
        Accelerometer_Data->y = (float)raw_y/Acc_Scale_Factor;
        Accelerometer_Data->z = (float)raw_z/Acc_Scale_Factor;
}

float MPU60X0::Get_Temperature(void)
{
	uint8_t receive_data[2];
	int16_t reg_value=0;

	HAL_I2C_Mem_Read(_hi2c_x,MPU60X0_ADD<<1,TEMP_OUT_H,I2C_MEMADD_SIZE_8BIT,receive_data,2,2000);
	
        reg_value =(int16_t)((receive_data[0]<<8) | receive_data[1]);

	/* Return temperature in C degrees */
	return (float)((float)reg_value/340.0 + 36.53);
}