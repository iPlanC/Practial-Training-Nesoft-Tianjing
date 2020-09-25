#include "mylib.h"

int main(void) {
	RCC_init();
	LED_init();
	KEY_init();
	PIR_init();
	BEEP_init();
	
	while (1) {
		if (((PIR_Scan(GPIOA, GPIO_Pin_6) == KEY_ON) || (KEY_Scan(GPIOA, GPIO_Pin_5) == KEY_ON))) {
			while (KEY_Scan(GPIOA, GPIO_Pin_0) != KEY_ON) {
				LED_TOGGLE;
				BEEP_TOGGLE;
				delay(0xFFFFF);
			}
			GPIO_WriteBit(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4, Bit_RESET);
		}
	}
}
