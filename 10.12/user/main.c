#include "mylib.h"

int main(void) {
	
	RCC_init();
	RTC_init();
	USART_init();
	SysTick_init();
	
	Set_Time();
	
	while (1) {
		Get_Time();
		delayus(1000000);
	}
}
