#include "mylib.h"
#include <stdio.h>

int main(void) {
	int i = 0;
	char *str;
	RCC_init();
	USART_init();
	SysTick_init();
	
	while (1) {
		//USART_SendData(USART1, 'a');
		//USART_SendString(USART1, "Hello World\n", 13);
		sprintf(str, "i = %d\n", i++);
		USART_SendString(USART1, str, strlen(str));
		delay(1000000);
	}
}
