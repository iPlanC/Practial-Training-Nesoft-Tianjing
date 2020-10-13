#include "mylib.h"

unsigned int timer;
unsigned char WWDG_CNT;
unsigned char arr[100];

void delayus(unsigned int us) {
	timer = us;
	SysTick->CTRL |= (1 << 0);
	while (timer);
	SysTick->CTRL &= ~(1 << 0);
}

void GPIO_init(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode) {
	GPIO_InitTypeDef GPIOA_init;
	
	GPIOA_init.GPIO_Pin = GPIO_Pin_x;
	GPIOA_init.GPIO_Speed = GPIO_Speed;
	GPIOA_init.GPIO_Mode = GPIO_Mode;
	
	GPIO_Init(GPIOx, &GPIOA_init);
}

void LED_init(void) {
	GPIO_init(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}

void BEEP_init(void) {
	GPIO_init(GPIOA, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}

void KEY_init(void) {
	GPIO_init(GPIOA, GPIO_Pin_0 | GPIO_Pin_5, GPIO_Speed_50MHz, GPIO_Mode_IPU);
}

void PIR_init(void) {
	GPIO_init(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IPD);
}

void RELAY_init(void) {
	GPIO_init(GPIOA, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}

void MQ_init(void) {
	GPIO_init(GPIOA, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_IPD);
}

void RCC_init(void) {
	#ifdef USE_WWDG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	#endif
	
	#ifdef USE_USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	#endif
	
	#ifdef USE_AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	#endif
	
	#ifdef USE_GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	#endif
	
	#ifdef USE_GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	#endif
	
	#ifdef USE_USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	#endif
	
	#ifdef USE_DMA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	#endif
}

void SysTick_init(void) {
	while (SysTick_Config(72));
	SysTick->CTRL &= ~(1 << 0);
}

void IWDG_init(void) {
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2500);
	IWDG_ReloadCounter();
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
	IWDG_Enable();
}

void USART_init(void) {
	USART_InitTypeDef USART_init;
//	NVIC_InitTypeDef NVIC_init;
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//	NVIC_init.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_init.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_init.NVIC_IRQChannelSubPriority = 2;
//	NVIC_init.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_init);
	
	GPIO_init(GPIOA, GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
//	GPIO_init(GPIOA, GPIO_Pin_10, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
//	GPIO_init(GPIOA, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
//	GPIO_init(GPIOA, GPIO_Pin_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
	
	USART_init.USART_BaudRate = 115200;
	USART_init.USART_WordLength = USART_WordLength_8b;
	USART_init.USART_StopBits = USART_StopBits_1;
	USART_init.USART_Parity = USART_Parity_No;
	USART_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_init.USART_Mode = USART_Mode_Tx;
	USART_Init(USART1, &USART_init);
	
//	USART_init.USART_BaudRate = 2400;
//	USART_init.USART_Mode = USART_Mode_Rx;
//	USART_Init(USART2, &USART_init);
//	
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
//	USART_Cmd(USART2, ENABLE);
}

void DMA_init(void) {
	DMA_InitTypeDef DMA_InitStructure;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_BASE + 0x04;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)arr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 100;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel4, ENABLE);
}

void USART_SendString(USART_TypeDef* USARTx, char* str, int length) {
	int i = 0;
	for (i = 0; i < length; i++) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USARTx, str[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	}
}

void WWDG_NVIC_init() {
	NVIC_InitTypeDef NVIC_init;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_init.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_init.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_init.NVIC_IRQChannelSubPriority = 1;
	NVIC_init.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_init);
}

void WWDG_init(unsigned char counter, unsigned char value, unsigned int prescaler) {
	WWDG_CNT = counter;
	WWDG_SetWindowValue(value);
	WWDG_SetPrescaler(prescaler);
	
	WWDG_NVIC_init();
	WWDG_ClearFlag();
	WWDG_EnableIT();
	
	WWDG_Enable(counter);
}

int KEY_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x) {
	int i = 0;
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == 0x0) {
		delayus(0xF);
		while ((GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == 0x0) && (i < 0xFFFFF)) i++;
		if (i < 0xFFFFF) {
			return KEY_ON;
		}
		else {
			return KEY_LONG;
		}
	}
	return KEY_OFF;
}

int PIR_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x) {
	return KEY_Scan(GPIOx, GPIO_Pin_x);
}

int MQ_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x) {
	return KEY_Scan(GPIOx, GPIO_Pin_x);
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) == SET) {
		GPIOA->ODR ^= GPIO_Pin_1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI9_5_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line5) == SET) {
		GPIOA->ODR ^= GPIO_Pin_2;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

void WWDG_IRQHandler(void) {
	WWDG_ClearFlag();
	WWDG_SetCounter(WWDG_CNT);
}

void USART2_IRQHandler(void) {
	unsigned char ch;
	static int i = 1;
	static int flag = 0;
	static unsigned char str[] = {0, 0, 0, 0, 0, 0, 0};
	while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET) {
		ch = USART_ReceiveData(USART2);
		
		if (ch == 0xAA) {
			str[0] = 0xAA;
			flag = 1;
		}
		if (ch != 0xAA && flag == 1) {
			str[i++] = ch;
			if (i == 7) {
				flag = 0;
				i = 1;
				if ((str[1] + str[2] + str[3] + str[4] == str[5]) && (str[6] == 0xFF)) {
					printf("%fv, ", (double)(((double)str[1] * 256 + (double)str[2]) / 1024 * 5));
					printf("0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x.\n", str[0], str[1], str[2], str[3], str[4], str[5], str[6]);
				}
			}
		}
	}
}

int fputc(int c, FILE *fp) {
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return 0;
}
