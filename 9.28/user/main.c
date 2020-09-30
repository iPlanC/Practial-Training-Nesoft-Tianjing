#include "mylib.h"

int main(void) {
	RCC_init();
	SysTick_init();
	LED_init();
	
	while (1) {
		delay(1000000);
		LED_TOGGLE;
	}
}
