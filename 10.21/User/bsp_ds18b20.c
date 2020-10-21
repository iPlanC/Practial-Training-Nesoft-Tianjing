#include  "bsp_ds18b20.h"

unsigned char ds18b20_id[2][8] = {0x28, 0xFF, 0x64, 0x2E, 0x31, 0x18, 0x02, 0x70,
																	0x28, 0xB5, 0x07, 0x79, 0xA2, 0x00, 0x03, 0xC3
};

void DS18B20_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS18B20_Mode_IPU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//PB:DS18B20_DQ
void DS18B20_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS18B20_Init(void)
{
	DS18B20_Mode_Out_PP();
	
	DS18B20_DATA_OUT(0);
	Delay_us(750);
	DS18B20_DATA_OUT(1);
	Delay_us(15);
	
	DS18B20_Mode_IPU();
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) != 0);
	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0);
}

void DS18B20_Write_Byte(unsigned char dat)
{
	unsigned int i;
	
	DS18B20_Mode_Out_PP();
	
	for(i = 0; i < 8; i++)
	{
		if(dat & 0x1)
		{
			DS18B20_DATA_OUT(0);
			Delay_us(8);
			
			DS18B20_DATA_OUT(1);
			Delay_us(58);
		}
		else
		{
			DS18B20_DATA_OUT(0);
			Delay_us(70);
			DS18B20_DATA_OUT(1);
			Delay_us(2);
		}
		dat = dat >> 1;
	}
}

unsigned char DS18B20_Read_Byte(void)
{
	unsigned int i;
	unsigned char dat = 0;
	
	for(i = 0; i < 8; i++)
	{
		DS18B20_Mode_Out_PP();
		DS18B20_DATA_OUT(0);
		Delay_us(10);
		DS18B20_Mode_IPU();
		
		dat |= (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) << i);
		Delay_us(55);
	}
	
	return dat;
}

float DS18B20_Get_Temperature(unsigned int n)
{
	unsigned int i;
	unsigned char tp_lsb, tp_msb;
	short s_tp;
	float temperature;
	
	DS18B20_Init();
	DS18B20_Write_Byte(0x55);
	for(i = 0; i < 8; i++)
		DS18B20_Write_Byte(ds18b20_id[n][i]);
	DS18B20_Write_Byte(0x44);
	
	DS18B20_Init();
	DS18B20_Write_Byte(0x55);
	for(i = 0; i < 8; i++)
		DS18B20_Write_Byte(ds18b20_id[n][i]);
	DS18B20_Write_Byte(0xBE);
	
	tp_lsb = DS18B20_Read_Byte();
	tp_msb = DS18B20_Read_Byte();
	
	s_tp = tp_msb << 8;
	s_tp = s_tp | tp_lsb;
	
	if(s_tp < 0)  //¸ºÎÂ¶ÈÖµ
		temperature = 0 - (~s_tp + 1) * 0.0625;
	else
		temperature = s_tp * 0.0625;
	
	return temperature;	
}

void read_id(void)
{
	unsigned int i;
	unsigned char dat[8];
	
	DS18B20_Init();
	DS18B20_Write_Byte(0x33);
	
	for(i = 0; i < 8; i++)
	{
		dat[i] = DS18B20_Read_Byte();
		printf("%c", dat[i]);
	}
	
}

