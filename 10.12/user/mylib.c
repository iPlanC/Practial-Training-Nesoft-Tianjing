#include "mylib.h"

unsigned int timer;

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

void LED_init() {
	GPIO_init(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}

void RCC_init(void) {
	#ifdef USE_WWDG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	#endif
	
	#ifdef USE_USART2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	#endif
	
	#ifdef USE_RTC
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	#endif
	
	#ifdef USE_TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
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

void TIM_init() {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	SysTick_init();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 9999;
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

void SysTick_init() {
	while (SysTick_Config(72));
	SysTick->CTRL &= ~(1 << 0);
}

void TIM2_IRQHandler() {
	if (TIM_GetFlagStatus(TIM2, TIM_IT_Update) == SET) {
		LED_TOGGLE;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
