#include "mylib.h"

extern unsigned char arr[100];

int main(void) {
	int i = 0;
	
	RCC_init();
	SysTick_init();
	LED_init();
	USART_init();
	DMA_init();
	
	for (i = 0; i < 100; i++) {
		arr[i] = 'a';
	}
	
	while (1) {
		LED_TOGGLE;
		delayus(100000);
	}
}
