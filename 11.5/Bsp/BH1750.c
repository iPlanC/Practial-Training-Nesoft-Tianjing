#include "delay.h"
#include "BH1750.h"

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
	delay_us(5);
	
	IIC_SDA_L;
	IIC_SCL_L;
}

void IIC_STOP(void)
{
	SDA_OUT();
	
	IIC_SDA_L;
	IIC_SCL_H;
	delay_us(5);
	
	IIC_SDA_H;
	IIC_SCL_L;
	
	delay_us(10000);
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
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
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

uint8_t BH1750_Byte_Write(uint8_t data)
{
	IIC_START();
	IIC_Send_Byte(BH1750_Addr|0);
	if(IIC_Wait_ACK()==1)
		return 1;
	IIC_Send_Byte(data);
	if(IIC_Wait_ACK()==1)
		return 2;
	IIC_STOP();
}

uint16_t BH1750_Read_Measure(void)
{
    uint16_t receive_data=0;
	IIC_START();
	IIC_Send_Byte(BH1750_Addr|1);
	if(IIC_Wait_ACK()==1)
		return 0;
	receive_data=IIC_Receive_Byte();
	IIC_ACK();
	receive_data=(receive_data<<8)+IIC_Receive_Byte();
	IIC_NAck();
    IIC_STOP();
	return receive_data;
}

void BH1750_Power_ON(void)
{
 
	BH1750_Byte_Write(POWER_ON);
	
}

void BH1750_Power_OFF(void)
{
	BH1750_Byte_Write(POWER_OFF);
}

void BH1750_RESET(void)
{
	BH1750_Byte_Write(MODULE_RESET);
}

void BH1750_Init(void)
{
	BH1750_Power_ON();
	BH1750_Byte_Write(Measure_Mode);
	delay_ms(120);
}

float LIght_Intensity(void)
{
	return (float)(BH1750_Read_Measure()/1.2f);
}
