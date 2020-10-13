#include "mylib.h"

unsigned int timer;
unsigned char WWDG_CNT;
uint16_t data;

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
	
	#ifdef USE_ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	#endif
	
	#ifdef USE_DMA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	#endif
}

void ADC_init() {
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_BASE + 0x4C;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&data;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 12;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_55Cycles5);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC2) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC2) == SET);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
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

void SysTick_init(void) {
	while (SysTick_Config(72));
	SysTick->CTRL &= ~(1 << 0);
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

int fputc(int c, FILE *fp) {
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return 0;
}
