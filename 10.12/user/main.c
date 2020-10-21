#include "mylib.h"

extern unsigned int timer;

int main(void) {
	int time = 0;
	
	RCC_init();
	USART_init();
	TIM_PWM_init();
	
	while (1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		delayus(15);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		
		TIM_Cmd(TIM2, ENABLE);
		while (KEY_Scan(GPIOA, GPIO_Pin_1) == 1) {
			if (TIM_GetCounter(TIM2) >= 0xFFFF) continue;
		}
		TIM_SetCounter(TIM2, 0);
		while (KEY_Scan(GPIOA, GPIO_Pin_1) != 1);
		TIM_Cmd(TIM2, DISABLE);
		
		time = TIM_GetCounter(TIM2);
		
		printf("Counter = %d\t", time);
		printf("Distance = %.2fcm\n", time * 0.00034 / 2 * 100);
		
		LED_TOGGLE3;
		delayus(time / 1000 * 10000);
		LED_TOGGLE3;
		delayus(time / 1000 * 10000);
		
		delayus(300);
	}
}
