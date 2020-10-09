#include "mylib.h"

unsigned int timer;
unsigned char WWDG_CNT;

void delay(unsigned int us) {
	timer = us;
	SysTick->CTRL |= (1 << 0);
	while (timer);
	SysTick->CTRL &= ~(1 << 0);
}

void LED_init(void) {
	GPIO_InitTypeDef GPIO_A_LED_init;
	
	GPIO_A_LED_init.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_A_LED_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_LED_init.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA, &GPIO_A_LED_init);
}

void BEEP_init(void) {
	GPIO_InitTypeDef GPIO_B_BEEP_init;
	
	GPIO_B_BEEP_init.GPIO_Pin = GPIO_Pin_8;
	GPIO_B_BEEP_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_B_BEEP_init.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOB, &GPIO_B_BEEP_init);
}

void KEY_init(void) {
	GPIO_InitTypeDef GPIO_A_LED_init;
	
	GPIO_A_LED_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5;
	GPIO_A_LED_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_LED_init.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOA, &GPIO_A_LED_init);
}

void PIR_init(void) {
	GPIO_InitTypeDef GPIO_A_PIR_init;
	
	GPIO_A_PIR_init.GPIO_Pin = GPIO_Pin_6;
	GPIO_A_PIR_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_PIR_init.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(GPIOA, &GPIO_A_PIR_init);
}

void RELAY_init(void) {
	GPIO_InitTypeDef GPIO_A_RELAY_init;
	
	GPIO_A_RELAY_init.GPIO_Pin = GPIO_Pin_7;
	GPIO_A_RELAY_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_RELAY_init.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA, &GPIO_A_RELAY_init);
}

void MQ_init(void) {
	GPIO_InitTypeDef GPIO_A_MQ_init;
	
	GPIO_A_MQ_init.GPIO_Pin = GPIO_Pin_8;
	GPIO_A_MQ_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_MQ_init.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(GPIOA, &GPIO_A_MQ_init);
}

void EXTI_init(void) {
	NVIC_InitTypeDef NVIC_init;
	GPIO_InitTypeDef GPIO_init;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_init.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_init.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_init.NVIC_IRQChannelSubPriority = 1;
	NVIC_init.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_init);
	
	NVIC_init.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_init);
	
	GPIO_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5;
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_init);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0 | GPIO_PinSource5);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void RCC_init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
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
		delay(0xF);
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
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) != 0x0) {
		return KEY_ON;
	}
	return KEY_OFF;
}

int MQ_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x) {
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) != 0x0) {
		return KEY_ON;
	}
	return KEY_OFF;
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
	// while (WWDG_GetFlagStatus() == SET);
	WWDG_SetCounter(WWDG_CNT);
}
