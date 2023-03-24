#ifndef __HX711_H__
#define __HX711_H__

#include "stm32f1xx_hal.h"
#include "main.h"

#define bufferSize 255

uint32_t readCount(void);
uint32_t HX711_GetWeight(void);

#endif
