#ifndef __HX711_H__
#define __HX711_H__

#include "stm32f1xx_hal.h"
#include "main.h"

#define GapValue 1000

#define	HX711_SCK_HIGH	HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_SET)
#define HX711_SCK_LOW		HAL_GPIO_WritePin(HX711_SCK_GPIO_Port, HX711_SCK_Pin, GPIO_PIN_RESET)
#define HX711_DT_OUT		HAL_GPIO_ReadPin(HX711_DT_GPIO_Port, HX711_DT_Pin)

unsigned long HX711_Read(void);
long HX711_GetWeight(void);

#endif
