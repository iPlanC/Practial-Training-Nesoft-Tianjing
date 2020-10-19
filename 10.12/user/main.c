#include "mylib.h"

extern unsigned int timer;

int main(void) {
	RCC_init();
	USART_init();
	TIM_init();
	
	GPIO_init(GPIOA, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
	GPIO_init(GPIOA, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
	
	while (1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		delayus_TIM(15);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		
		TIM_Cmd(TIM3, ENABLE);
		while (KEY_Scan(GPIOA, GPIO_Pin_1) != KEY_OFF);
		TIM_Cmd(TIM3, DISABLE);
		
		printf("Distance = %d\n", timer * 340 / 2);
		
		delayus_TIM(60);
	}
}
