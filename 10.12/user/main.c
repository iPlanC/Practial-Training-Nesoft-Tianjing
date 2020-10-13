#include "mylib.h"

#define V25         (float)1775    // 0x06EF
#define AVG_SLOPE   (float)  58    // 0x003A

extern uint16_t data;

int main(void) {
	RCC_init();
	ADC_init();
	USART_init();
	
	while (1) {
		printf("Vsence: %d\t", data);
		printf("Temp: %f\n", ((V25 - data) / AVG_SLOPE) + 25);
	}
}
