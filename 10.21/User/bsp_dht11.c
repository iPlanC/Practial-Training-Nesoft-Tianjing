#include "bsp_dht11.h"

unsigned char Hum_H, Hum_L, Tem_H, Tem_L;

//PA7:DHT11_DATA
void DHT11_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Mode_IPU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DHT11_Start(void)
{
	unsigned int timeout;
	
	DHT11_Mode_Out_PP();  //将PA7配置为输出模式
	DHT11_DATA_OUT(0); 		//将电平拉低
	Delay_us(20000);			//保持低电平至少18ms
	DHT11_DATA_OUT(1); 		//将电平拉高
	Delay_us(30);					//保持高电平20~40us
	
	DHT11_Mode_IPU();
	
	//DHT11的80us低电平响应信号
	timeout = 80;
	while((!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)) && (timeout > 0))
	{
		timeout--;
		Delay_us(1);
	}
	//DHT11的80us高电平响应信号	
	timeout = 80;
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) && (timeout > 0))
	{
		timeout--;
		Delay_us(1);
	}
}

unsigned char DHT11_Read_Byte(void)
{
	unsigned int i;
	unsigned char dat = 0;
	unsigned int timeout;
	
	DHT11_Mode_IPU();
	
	for(i = 0; i < 8; i++)
	{
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0);  //等待50us过去
		
		Delay_us(40);  //跨过40us后再去读取信号线上的电平，如果为低电平标识数据为0，如果为高电平表示数据为1
	
		dat <<= 1;
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7))
			dat += 1;
		
		timeout = 50;
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) && (timeout > 0))
		{
			timeout--;
			Delay_us(1);
		}		
	}
	
	return dat;
}

void DHT11_Read(void)
{
	unsigned char Hum_H_temp, Hum_L_temp, Tem_H_temp, Tem_L_temp, Check_Sum;
	
	//启动DHT11
	DHT11_Start();		
	
	//连续读取5个Byte，共计40bit，内含湿度8位整数位，湿度8位小数位，温度8位整数位，温度8位小数位，校验和
	Hum_H_temp = DHT11_Read_Byte();	
	Hum_L_temp = DHT11_Read_Byte();	
	Tem_H_temp = DHT11_Read_Byte();	
	Tem_L_temp = DHT11_Read_Byte();	
	Check_Sum  = DHT11_Read_Byte();	
	
	//发送结束标志
	DHT11_Mode_Out_PP();
	DHT11_DATA_OUT(1); 		//将电平拉高

	//判断读取的40bit数据是否有效，及检查校验和是否正确
	if((Hum_H_temp + Hum_L_temp + Tem_H_temp + Tem_L_temp) == Check_Sum)
	{
		Hum_H = Hum_H_temp;
		Hum_L = Hum_L_temp;
		Tem_H = Tem_H_temp;
		Tem_L = Tem_L_temp;
	}
}


