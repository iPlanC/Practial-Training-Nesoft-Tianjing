#include "mylib.h"

int main(void) {
	
	RCC_init();
	RTC_init();
	USART_init();
	SysTick_init();
	
	while (1) {
		Set_Time();
		Get_Time();
		delayus(1000000);
	}
}
