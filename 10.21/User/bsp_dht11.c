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
	
	DHT11_Mode_Out_PP();  //��PA7����Ϊ���ģʽ
	DHT11_DATA_OUT(0); 		//����ƽ����
	Delay_us(20000);			//���ֵ͵�ƽ����18ms
	DHT11_DATA_OUT(1); 		//����ƽ����
	Delay_us(30);					//���ָߵ�ƽ20~40us
	
	DHT11_Mode_IPU();
	
	//DHT11��80us�͵�ƽ��Ӧ�ź�
	timeout = 80;
	while((!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)) && (timeout > 0))
	{
		timeout--;
		Delay_us(1);
	}
	//DHT11��80us�ߵ�ƽ��Ӧ�ź�	
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
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0);  //�ȴ�50us��ȥ
		
		Delay_us(40);  //���40us����ȥ��ȡ�ź����ϵĵ�ƽ�����Ϊ�͵�ƽ��ʶ����Ϊ0�����Ϊ�ߵ�ƽ��ʾ����Ϊ1
	
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
	
	//����DHT11
	DHT11_Start();		
	
	//������ȡ5��Byte������40bit���ں�ʪ��8λ����λ��ʪ��8λС��λ���¶�8λ����λ���¶�8λС��λ��У���
	Hum_H_temp = DHT11_Read_Byte();	
	Hum_L_temp = DHT11_Read_Byte();	
	Tem_H_temp = DHT11_Read_Byte();	
	Tem_L_temp = DHT11_Read_Byte();	
	Check_Sum  = DHT11_Read_Byte();	
	
	//���ͽ�����־
	DHT11_Mode_Out_PP();
	DHT11_DATA_OUT(1); 		//����ƽ����

	//�ж϶�ȡ��40bit�����Ƿ���Ч�������У����Ƿ���ȷ
	if((Hum_H_temp + Hum_L_temp + Tem_H_temp + Tem_L_temp) == Check_Sum)
	{
		Hum_H = Hum_H_temp;
		Hum_L = Hum_L_temp;
		Tem_H = Tem_H_temp;
		Tem_L = Tem_L_temp;
	}
}


