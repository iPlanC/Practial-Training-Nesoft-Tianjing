#include "bsp_iic_bh1750.h"

void BH1750_Write_Cmd(unsigned char cmd)
{
	IIC_START();
	IIC_Send_Byte(BH1750_ADDR);  //write
	while(IIC_Wait_ACK());
	IIC_Send_Byte(cmd);
	while(IIC_Wait_ACK());
	IIC_STOP();
}

unsigned int BH1750_Read_Result(void)
{
	unsigned int data_h, data_l;
	
	IIC_START();
	IIC_Send_Byte(BH1750_ADDR + 1);  //Read
	while(IIC_Wait_ACK());
	data_h = IIC_Receive_Byte();
	IIC_ACK();
	data_l = IIC_Receive_Byte();
	IIC_STOP();
	
	return ((data_h << 8) | data_l);
}
