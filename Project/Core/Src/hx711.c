#include "hx711.h"

#include "tim.h"
#include "main.h"

long HX711_Buffer = 0;
long weightValue = 0;
long firstWeightValue = 0;

unsigned long HX711_Read(void)
{
	unsigned long count; 
	unsigned char i;
	HAL_GPIO_WritePin(HX711_DT_GPIO_Port, HX711_DT_Pin, GPIO_PIN_SET);
	HAL_Delay_us(1);
	HX711_SCK_LOW;
	HAL_Delay_us(1);
  count=0; 
  while(HX711_DT_OUT); 
  for(i=0;i<24;i++)
	{ 
	  HX711_SCK_HIGH; 
		HAL_Delay_us(1);
	  count=count<<1; 
		HX711_SCK_LOW; 
		HAL_Delay_us(1);
	  if(HX711_DT_OUT)
		{
			count++;
		}			
	} 
 	HX711_SCK_HIGH; 
	count^=0x800000;
	HAL_Delay_us(1);
	HX711_SCK_LOW; 
	HAL_Delay_us(1);
	return(count);
}

long HX711_GetWeight(void)
{
	HX711_Buffer = HX711_Read();
	if(firstWeightValue>=HX711_Buffer)
	{
		HX711_Buffer = firstWeightValue-HX711_Buffer;
		HX711_Buffer = HX711_Buffer/100;
	}
	else
	{
		HX711_Buffer = HX711_Buffer-firstWeightValue;
		HX711_Buffer = HX711_Buffer/100;
	}
	return HX711_Buffer;
}
