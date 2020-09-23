#include <stm32f10x.h>
#include "led_key.h"

int main(void) {
	RCC_init();
	LED_init();
	KEY_init();
	
	while (1) {
		if (KEY_Scan(GPIOA, GPIO_Pin_0) == KEY_ON) {
			GPIOA->ODR ^= (GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		}
	}
}
