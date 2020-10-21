#include "bsp_iic.h"

//PB6:SCL  PB7:SDA	
void IIC1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOB, GPIO_Pin_6 | GPIO_Pin_7, Bit_RESET);
}

void IIC_START(void)
{
	SDA_OUT();
	
	IIC_SDA_H;
	IIC_SCL_H;
	Delay_us(5);
	
	IIC_SDA_L;
	IIC_SCL_L;
}

void IIC_STOP(void)
{
	SDA_OUT();
	
	IIC_SDA_L;
	IIC_SCL_H;
	Delay_us(5);
	
	IIC_SDA_H;
	IIC_SCL_L;
	
	Delay_us(10000);
}

//return 0: reveived ACK  return 1: no ACK
unsigned int IIC_Wait_ACK(void)
{
	unsigned int n = 0;
	
	SDA_IN();
	IIC_SCL_H;
	
	while(Read_SDA)
	{
		n++;
		if(n > 500)
		{
			IIC_STOP();
			return 1;
		}
	}
	
	IIC_SCL_L;
	return 0;
}

void IIC_ACK(void)
{
	SDA_OUT();
	
	IIC_SCL_L;
	IIC_SDA_L;
	IIC_SCL_H;
	
	IIC_SCL_L;
}

void IIC_Send_Byte(unsigned char data)
{
	unsigned int i;
	
	SDA_OUT();
	
	for(i = 0; i < 8; i++)
	{
		if(data & 0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		
		IIC_SCL_L;
		IIC_SCL_H;
		
		IIC_SCL_L;
		data <<= 1;
	}
}

unsigned char IIC_Receive_Byte(void)
{
	unsigned int i;
	unsigned char data;
	
	SDA_IN();
	
	for(i = 0; i < 8; i++)
	{
		IIC_SCL_L;
		IIC_SCL_H;
		
		data <<= 1;
		
		if(Read_SDA)
			data++;
		
		IIC_SCL_L;			
	}

	return data;
}
