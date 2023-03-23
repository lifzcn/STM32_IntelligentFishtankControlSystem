#include "ds18b20.h"
#include "main.h"
#include "tim.h"

void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.Pin=DS18B20_Pin;
  GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull=GPIO_PULLUP;
  GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;
  HAL_GPIO_Init(DS18B20_GPIO_Port,&GPIO_InitStructure);
}

void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.Pin=DS18B20_Pin;
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull=GPIO_PULLUP;
  GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;
  HAL_GPIO_Init(DS18B20_GPIO_Port,&GPIO_InitStructure);
}

void DS18B20_Reset(void)	   
{                 
	DS18B20_IO_OUT();
	DS18B20_DQ_OUT_LOW;
	HAL_Delay_us(750);
	DS18B20_DQ_OUT_HIGH;
	HAL_Delay_us(15);
}

uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_IO_IN();
  while(DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		HAL_Delay_us(1);
	};	 
	if(retry>=200)
	{
		return 1;
	}
	else
	{
		retry=0;
	}
  while(!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		HAL_Delay_us(1);
	};
	if(retry>=240)
	{
		return 1;
	}		
	return 0;
}

uint8_t DS18B20_Read_Bit(void)
{
	uint8_t data;
	DS18B20_IO_OUT();
	DS18B20_DQ_OUT_LOW; 
	HAL_Delay_us(2);
	DS18B20_DQ_OUT_HIGH; 
	DS18B20_IO_IN();
	HAL_Delay_us(12);
	if(DS18B20_DQ_IN)
	{
		data=1;
	}
	else
	{
		data=0;
	}		
	HAL_Delay_us(50);           
	return data;
}


uint8_t DS18B20_Read_Byte(void)
{        
  uint8_t i,j,dat;
  dat=0;
	for(i=1;i<=8;i++) 
	{
		j=DS18B20_Read_Bit();
    dat=(j<<7)|(dat>>1);
	}						    
	return dat;
}

void DS18B20_Write_Byte(uint8_t dat)     
{             
	uint8_t j;
  uint8_t testb;
	DS18B20_IO_OUT();
  for (j=1;j<=8;j++) 
	{
		testb=dat&0x01;
    dat=dat>>1;
    if(testb) 
    {
			DS18B20_DQ_OUT_LOW;
      HAL_Delay_us(2);                            
      DS18B20_DQ_OUT_HIGH;
      HAL_Delay_us(60);
		}
		else
		{
			DS18B20_DQ_OUT_LOW;
      HAL_Delay_us(60);          
      DS18B20_DQ_OUT_HIGH;
      HAL_Delay_us(2);                          
		}
	}
}

void DS18B20_Start(void)
{   						               
	DS18B20_Reset();	   
	DS18B20_Check();	 
  DS18B20_Write_Byte(0xcc);
  DS18B20_Write_Byte(0x44);
} 
  	 
uint8_t DS18B20_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStructure.Pin=DS18B20_Pin;
  GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pull=GPIO_PULLUP;
  GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;
  HAL_GPIO_Init(DS18B20_GPIO_Port,&GPIO_InitStructure);
 	DS18B20_Reset();
	return DS18B20_Check();
}

float DS18B20_GetTemperture(void)
{
  uint16_t temp;
	uint8_t a,b;
	float value;
  DS18B20_Start();
  DS18B20_Reset();
  DS18B20_Check();	 
  DS18B20_Write_Byte(0xcc);
  DS18B20_Write_Byte(0xbe);	    
  a=DS18B20_Read_Byte(); 
  b=DS18B20_Read_Byte(); 
	temp=b;
	temp=(temp<<8)+a;
  if((temp&0xf800)==0xf800)
	{
		temp=(~temp)+1;
		value=temp*(-0.0625);
	}
	else
	{
		value=temp*0.0625;	
	}  
	return value;
}
