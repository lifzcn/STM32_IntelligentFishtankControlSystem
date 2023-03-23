#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "stm32f1xx_hal.h"
#include "main.h"

#define DS18B20_DQ_OUT_HIGH HAL_GPIO_WritePin(DS18B20_GPIO_Port,DS18B20_Pin,GPIO_PIN_SET)
#define DS18B20_DQ_OUT_LOW 	HAL_GPIO_WritePin(DS18B20_GPIO_Port,DS18B20_Pin,GPIO_PIN_RESET)
#define DS18B20_DQ_IN	 HAL_GPIO_ReadPin(DS18B20_GPIO_Port,DS18B20_Pin)

uint8_t DS18B20_Init(void);
float DS18B20_GetTemperture(void);
void DS18B20_Start(void);
void DS18B20_Write_Byte(uint8_t dat);
uint8_t DS18B20_Read_Byte(void);
uint8_t DS18B20_Read_Bit(void);
uint8_t DS18B20_Check(void);
void DS18B20_Reset(void);

#endif
