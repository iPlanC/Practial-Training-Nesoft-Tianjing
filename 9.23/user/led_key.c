#include "led_key.h"

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

void KEY_init(void) {
	GPIO_InitTypeDef GPIO_A_KEY_init;
	
	GPIO_A_KEY_init.GPIO_Pin = GPIO_Pin_0;
	GPIO_A_KEY_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_KEY_init.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOA, &GPIO_A_KEY_init);
}

void RCC_init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
}

int KEY_Scan(GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x) {
	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == 0x0) {
		delay(0xF);
		if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin_x) == 0x0) {
			return KEY_ON;
		}
	}
	return KEY_OFF;
}
