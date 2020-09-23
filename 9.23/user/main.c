#include <stm32f10x.h>

void delay(unsigned int loop) {
	while (loop--);
}

int main() {
	int i = 0;
	int flag = -1;
	
	GPIO_InitTypeDef GPIO_A_KEY_init;
	GPIO_InitTypeDef GPIO_A_LED_init;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	GPIO_A_KEY_init.GPIO_Pin = GPIO_Pin_0;
	GPIO_A_KEY_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_KEY_init.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_A_LED_init.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_A_LED_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_A_LED_init.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA, &GPIO_A_KEY_init);
	GPIO_Init(GPIOA, &GPIO_A_LED_init);
	
	while (1) {
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0x0) {
			if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0x0) {
				flag = -flag;
			}
		}
		
		if (flag == 1) {
			for (i = 1; i <= 4; i++) {
				GPIO_SetBits(GPIOA, (0x1 << i));
			}
		}
		else {
			for (i = 1; i <= 4; i++) {
				GPIO_ResetBits(GPIOA, (0x1 << i));
			}
		}
	}
}
