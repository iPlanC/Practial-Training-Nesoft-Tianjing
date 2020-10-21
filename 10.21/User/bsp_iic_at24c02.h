#ifndef __BSP_IIC_AT24C02_H__
#define __BSP_IIC_AT24C02_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"
#include "bsp_iic.h"

void IIC_Write_Byte(unsigned char Addr, unsigned char data);
void AT24C02_Write_Page(unsigned char Addr, unsigned char *buf);
void AT24C02_Write_Buf(unsigned char Addr, unsigned char *buf, unsigned int size);
unsigned char IIC_Read_Byte(unsigned char Addr);
void AT24C02_Read_Buf(unsigned char Addr, unsigned char *buf, unsigned int size);

#endif
