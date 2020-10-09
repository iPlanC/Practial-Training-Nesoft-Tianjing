#include "mylib.h"

int main(void) {
	int i = 5;
	
	RCC_init();
	LED_init();
	SysTick_init();
	
	while (i--) {
		delay(100000);
		LED_TOGGLE;
		delay(100000);
		LED_TOGGLE;
	}
	
	WWDG_init(0x7F, 0x5F, WWDG_Prescaler_8);
	
	while (1) {
		
	}
}
