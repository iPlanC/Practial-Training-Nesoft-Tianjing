#ifndef __BH1750__H_
#define __BH1750__H_

#include "bsp_i2c.h"
#include "delay.h"

#define BH1750_Addr 0x46
#define POWER_OFF 0X00
#define POWER_ON  0X01
#define MODULE_RESET			0x07
#define	CONTINUE_H_MODE		0x10
#define CONTINUE_H_MODE2	0x11
#define CONTINUE_L_MODE		0x13
#define ONE_TIME_H_MODE		0x20
#define ONE_TIME_H_MODE2	0x21
#define ONE_TIME_L_MODE		0x23
#define Measure_Mode			CONTINUE_H_MODE

#define SDA_OUT()		{GPIOB->CRL &= 0x0FFFFFFF; GPIOB->CRL |= 0x30000000;}
#define SDA_IN()		{GPIOB->CRL &= 0x0FFFFFFF; GPIOB->CRL |= 0x40000000;}

#define IIC_SDA_H		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET)
#define IIC_SDA_L		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET)
#define IIC_SCL_H		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET)
#define IIC_SCL_L		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET)

#define Read_SDA		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)

#if ((Measure_Mode==CONTINUE_H_MODE2)|(Measure_Mode==ONE_TIME_H_MODE2))
	#define Resolurtion		0.5
#elif ((Measure_Mode==CONTINUE_H_MODE)|(Measure_Mode==ONE_TIME_H_MODE))
	#define Resolurtion		1
#elif ((Measure_Mode==CONTINUE_L_MODE)|(Measure_Mode==ONE_TIME_L_MODE))
	#define Resolurtion		4
#endif

void IIC1_Configuration(void);
void IIC_START(void);
void IIC_STOP(void);
unsigned int IIC_Wait_ACK(void);
void IIC_ACK(void);
void IIC_Send_Byte(unsigned char data);
unsigned char IIC_Receive_Byte(void);
void IIC_NAck(void);
void BH1750_Init(void);
float LIght_Intensity(void);
uint8_t BH1750_Byte_Write(uint8_t data);
uint16_t BH1750_Read_Measure(void);
void BH1750_Power_ON(void);
void BH1750_Power_OFF(void);
void BH1750_RESET(void);

#endif
