#include "mylib.h"

void delay(unsigned int loop) {
	while (loop--);
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

void RCC_init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
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
