#include "mylib.h"

int main(void) {
	RCC_init();
	MQ_init();
	BEEP_init();
	
	while (1) {
		if (MQ_Scan(GPIOA, GPIO_Pin_8) == KEY_ON) {
			BEEP_TOGGLE;
			delay(0xFFF);
		}
	}
}
