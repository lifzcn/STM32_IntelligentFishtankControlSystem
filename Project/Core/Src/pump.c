#include "pump.h"

void addWater()
{
	HAL_GPIO_WritePin(Pump1_IN1_GPIO_Port, Pump1_IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Pump2_IN2_GPIO_Port, Pump2_IN2_Pin, GPIO_PIN_RESET);
}

void subtractWater()
{
	HAL_GPIO_WritePin(Pump1_IN3_GPIO_Port, Pump1_IN3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Pump2_IN4_GPIO_Port, Pump2_IN4_Pin, GPIO_PIN_RESET);
}
