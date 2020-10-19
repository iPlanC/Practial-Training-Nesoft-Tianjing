#include "mylib.h"

extern unsigned int timer;

int main(void) {
	unsigned int i = 0;
	RCC_init();
//	USART_init();
//	TIM_init();
	TIM_PWM_init();
	
	while (1) {
		for (i = 0; i < 65536; i++) {
			TIM_SetCompare2(TIM2, i);
			delayus(20);
		}
		for (i = 65535; i > 0; i--) {
			TIM_SetCompare2(TIM2, i);
			delayus(20);
		}
	}
	
//	GPIO_init(GPIOA, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_IPD);
//	GPIO_init(GPIOA, GPIO_Pin_2, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
//	
//	while (1) {
//		GPIO_SetBits(GPIOA, GPIO_Pin_2);
//		delayus_TIM(15);
//		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
//		
//		TIM_Cmd(TIM2, ENABLE);
//		while (KEY_Scan(GPIOA, GPIO_Pin_1) != KEY_OFF);
//		TIM_Cmd(TIM2, DISABLE);
//		
//		printf("Distance = %d\n", timer * 340 / 2);
//		
//		delayus_TIM(60);
//	}
}
