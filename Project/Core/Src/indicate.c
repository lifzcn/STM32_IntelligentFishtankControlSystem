#include "indicate.h"

void addHeat()
{
	HAL_GPIO_WritePin(LED_Up_GPIO_Port, LED_Up_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LEDGND_Up_GPIO_Port, LEDGND_Up_Pin, GPIO_PIN_RESET);
}

void subtractHeat()
{
	HAL_GPIO_WritePin(LED_Down_GPIO_Port, LED_Down_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LEDGND_Down_GPIO_Port, LEDGND_Down_Pin, GPIO_PIN_RESET);
}
