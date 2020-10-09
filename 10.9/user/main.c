#include "mylib.h"

int main(void) {
	RCC_init();
	USART_init();
	SysTick_init();
	
	while (1) {
		//USART_SendData(USART1, 'a');
		USART_SendString(USART1, "Hello World\n", 13);
		delay(1000000);
	}
}
