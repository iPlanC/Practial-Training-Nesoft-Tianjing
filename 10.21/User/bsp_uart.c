#include "bsp_uart.h"
#include "bsp_SysTick.h"
#include "bsp_iic_at24c02.h"

unsigned char buf[10];
int i = 0;

void Uart1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   //TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;   //TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

void Uart1_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART_SendString(const unsigned char *pt)
{
	while(*pt)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);//确保发送缓冲区为空，只有发送缓冲区为空才继续发送
		USART_SendData(USART1, *pt);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);//等待发送完成
		pt++;
	}
}

int fputc (int c, FILE *fp)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);//确保发送缓冲区为空，只有发送缓冲区为空才继续发送
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);//等待发送完成
	
	return 0;
}

int fgetc(FILE *fp)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != SET);  //等待直到接收缓冲区内非空
	return (int)USART_ReceiveData(USART1);
}

//void USART1_IRQHandler(void)
//{
//	unsigned char ch;
//	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
//	{
//		ch = USART_ReceiveData(USART1);
//		printf("%c\n", ch + 1);
//	}			
//}

void control_LED(unsigned int led_number, unsigned int status)
{
	GPIO_WriteBit(GPIOA, (uint16_t)1<<led_number, (BitAction)status);
}

void USART1_IRQHandler(void)
{
	printf("USART1_IRQHandler\n");
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		//AT24C02_Write_Page(0x0, IIC_Read_Byte(0x0) * 10 + (USART_ReceiveData(USART1) - '0'));
		i = i * 10 + (USART_ReceiveData(USART1) - '0');
		IIC_Write_Byte(0x0, i);
		printf("3\n");
	}			
}

void Uart1_scanf(unsigned int *pt, unsigned int bits)
{
	unsigned int i = 0;
	
	unsigned int tmp[] = {0, 0 , 0, 0};

	while(i < bits)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		tmp[i++] = USART_ReceiveData(USART1);
	}
	
	if(bits == 4)
		*pt = (tmp[0] - '0')*1000 + (tmp[1] - '0')*100 + (tmp[2] - '0')*10 + (tmp[3] - '0');
	else
		*pt = (tmp[0] - '0')*10 + (tmp[1] - '0');
}

