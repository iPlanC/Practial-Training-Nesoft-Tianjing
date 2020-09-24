#include <stm32f10x.h>
#include "mylib.h"

int main(void) {
	int isboot = -1;
	RCC_init();
	LED_init();
	KEY_init();
	
	while (1) {
		switch (KEY_Scan(GPIOA, GPIO_Pin_0)) {
			case KEY_ON:
				// short press
				if (isboot == 1) LED_TOGGLE1;
				break;
			case KEY_LONG:
				// long press
				isboot = -isboot;
				if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0x1) LED_TOGGLE1; 
				LED_TOGGLE4;
				break;
		}
	}
}
