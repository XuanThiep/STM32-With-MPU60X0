#ifndef  __MPU_60X0_H
#define	 __MPU_60X0_H

#include "stm32f0xx_hal.h"

/* Define MPU60X0 7 bits I2C Slave Address, By default pin AD0 is connected to GND */
#define		MPU60X0_ADD		0x68

/* Define MPU60X0 Internal Register */
typedef enum 
{
	SELF_TEST_X = 0x0d,
	SELF_TEST_Y = 0x0e,
	SELF_TEST_Z = 0x0f,
	SELF_TEST_A = 0x10,
	SMPLRT_DIV = 0x19,
	CONFIG = 0x1a,
	GYRO_CONFIG = 0x1b,
	ACCEL_CONFIG = 0x1c,
	MOT_THR = 0x1f,
	FIFO_EN = 0x23,
	I2C_MST_CTRL = 0x24,
	I2C_SLV0_ADDR = 0x25,
	I2C_SLV0_REG = 0x26,
	I2C_SLV0_CTRL = 0x27,
	I2C_SLV1_ADDR = 0x28,
	I2C_SLV1_REG = 0x29,
	I2C_SLV1_CTRL = 0x2a,
	I2C_SLV2_ADDR = 0x2b,
	I2C_SLV2_REG = 0x2c,
	I2C_SLV2_CTRL = 0x2d,
	I2C_SLV3_ADDR = 0x2e,
	I2C_SLV3_REG = 0x2f,
	I2C_SLV3_CTR = 0x30,
	I2C_SLV4_ADDR = 0x31,
	I2C_SLV4_REG = 0x32,
	I2C_SLV4_DO = 0x33,
	I2C_SLV4_CTRL = 0x34,
	I2C_SLV4_D = 0x35,
	I2C_MST_STATUS = 0x36,
	INT_PIN_CFG = 0x37,
	INT_ENABLE = 0x38,
	INT_STATUS = 0x3a,
	ACCEL_XOUT_H = 0x3b,
	ACCEL_XOUT_L = 0x3c,
	ACCEL_YOUT_H = 0x3d,
	ACCEL_YOUT_L = 0x3e,
	ACCEL_ZOUT_H = 0x3f,
	ACCEL_ZOUT_L = 0x40,
	TEMP_OUT_H = 0x41,
	TEMP_OUT_L = 0x42,
	GYRO_XOUT_H = 0x43,
	GYRO_XOUT_L = 0x44,
	GYRO_YOUT_H = 0x45,
	GYRO_YOUT_L = 0x46,
	GYRO_ZOUT_H = 0x47,
	GYRO_ZOUT_L = 0x48,
	EXT_SENS_DATA_00 = 0x49,
	EXT_SENS_DATA_01 = 0x4a,
	EXT_SENS_DATA_02 = 0x4b,
	EXT_SENS_DATA_03 = 0x4c,
	EXT_SENS_DATA_04 = 0x4d,
	EXT_SENS_DATA_05 = 0x4e,
	EXT_SENS_DATA_06 = 0x4f,
	EXT_SENS_DATA_07 = 0x50,
	EXT_SENS_DATA_08 = 0x51,
	EXT_SENS_DATA_09 = 0x52,
	EXT_SENS_DATA_10 = 0x53,
	EXT_SENS_DATA_11 = 0x54,
	EXT_SENS_DATA_12 = 0x55,
	EXT_SENS_DATA_13 = 0x56,
	EXT_SENS_DATA_14 = 0x57,
	EXT_SENS_DATA_15 = 0x58,
	EXT_SENS_DATA_16 = 0x59,
	EXT_SENS_DATA_17 = 0x5a,
	EXT_SENS_DATA_18 = 0x5b,
	EXT_SENS_DATA_19 = 0x5c,
	EXT_SENS_DATA_20 = 0x5d,
	EXT_SENS_DATA_21 = 0x5e,
	EXT_SENS_DATA_22 = 0x5f,
	EXT_SENS_DATA_23 = 0x60,
	I2C_SLV0_DO = 0x63,
	I2C_SLV1_DO = 0x64,
	I2C_SLV2_DO = 0x65,
	I2C_SLV3_DO = 0x66,
	I2C_MST_DELAY_CTRL = 0x67,
	SIGNAL_PATH_RESET = 0x68,
	MOT_DETECT_CTRL = 0x69,
	USER_CTRL = 0x6a,
	PWR_MGMT_1 = 0x6b,
	PWR_MGMT_2 = 0x6c,
	FIFO_COUNTH = 0x72,
	FIFO_COUNTL = 0x73,
	FIFO_R_W = 0x74,
	WHO_AM_I = 0x75
}MPU_60X0_Register_Add;


/* Gyro sensitivities in °/s */
#define MPU60X0_GYRO_SENS_250           131.0
#define MPU60X0_GYRO_SENS_500		65.5
#define MPU60X0_GYRO_SENS_1000		32.8
#define MPU60X0_GYRO_SENS_2000		16.4

/* Acce sensitivities in g */
#define MPU60X0_ACCE_SENS_2		16384.0
#define MPU60X0_ACCE_SENS_4	        8192.0
#define MPU60X0_ACCE_SENS_8		4096.0
#define MPU60X0_ACCE_SENS_16		2048.0


/**
 * @brief  Parameters for accelerometer range
 */
typedef enum 
{
	MPU60X0_Accelerometer_2G = 0x00, /*!< Range is +- 2G */
	MPU60X0_Accelerometer_4G = 0x01, /*!< Range is +- 4G */
	MPU60X0_Accelerometer_8G = 0x02, /*!< Range is +- 8G */
	MPU60X0_Accelerometer_16G = 0x03 /*!< Range is +- 16G */
}MPU60X0_Accelerometer_t;


/**
 * @brief  Parameters for gyroscope range
 */
typedef enum 
{
	MPU60X0_Gyroscope_250s = 0x00,  /*!< Range is +- 250 degrees/s */
	MPU60X0_Gyroscope_500s = 0x01,  /*!< Range is +- 500 degrees/s */
	MPU60X0_Gyroscope_1000s = 0x02, /*!< Range is +- 1000 degrees/s */
	MPU60X0_Gyroscope_2000s = 0x03  /*!< Range is +- 2000 degrees/s */
}MPU60X0_Gyroscope_t;


typedef struct
{
  float x;
  float y;
  float z;
}MPU60X0_Data;

class MPU60X0
{
private:

	/* Store I2C information for connect to MPU60X0 */
	I2C_HandleTypeDef* _hi2c_x;
        float Acc_Scale_Factor;
        float Gyro_Scale_Factor;
public:
	/* Constructor */
	MPU60X0(void);
	MPU60X0(I2C_HandleTypeDef* hi2c_x);

	uint8_t Who_am_I(void);
	void Initialize(MPU60X0_Accelerometer_t AccelerometerSensitivity,MPU60X0_Gyroscope_t GyroscopeSensitivity);
	void Get_Gyroscope_value(MPU60X0_Data* Gyroscope_Data);
	void Get_Accelerometer_value(MPU60X0_Data* Accelerometer_Data);
	float Get_Temperature(void);
};

#endif	
