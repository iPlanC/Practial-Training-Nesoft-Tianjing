#include "bsp_iic_at24c02.h"

void IIC_Write_Byte(unsigned char Addr, unsigned char data)
{
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(data);
	while(IIC_Wait_ACK());
	IIC_STOP();
}

void AT24C02_Write_Page(unsigned char Addr, unsigned char *buf)
{
	unsigned int size = 8;
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	while(size--)
	{
		IIC_Send_Byte(*buf);
		while(IIC_Wait_ACK());
		buf++;
		Addr++;
	}
	IIC_STOP();
}

void AT24C02_Write_Buf(unsigned char Addr, unsigned char *buf, unsigned int size)
{
	while(size--)
	{
		IIC_Write_Byte(Addr, *buf);
		buf++;
		Addr++;
	}
}

unsigned char IIC_Read_Byte(unsigned char Addr)
{
	unsigned char data;
	
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	
	IIC_START();
	IIC_Send_Byte(0xA1);
	while(IIC_Wait_ACK());
	data = IIC_Receive_Byte();
	IIC_STOP();
	
	return data;
}

void AT24C02_Read_Buf(unsigned char Addr, unsigned char *buf, unsigned int size)
{
	IIC_START();
	IIC_Send_Byte(0xA0);
	while(IIC_Wait_ACK());
	IIC_Send_Byte(Addr);
	while(IIC_Wait_ACK());
	
	IIC_START();
	IIC_Send_Byte(0xA1);
	while(IIC_Wait_ACK());
	while(size > 1)
	{
		*buf = IIC_Receive_Byte();
		IIC_ACK();
		buf++;
		Addr++;
		size--;
	}
	
	*buf = IIC_Receive_Byte();
	IIC_STOP();
}
