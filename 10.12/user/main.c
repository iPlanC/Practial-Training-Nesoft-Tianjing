#include "mylib.h"

#define V25         (float)1775    // 0x06EF
#define AVG_SLOPE   (float)  58    // 0x003A

extern uint16_t Deepdata;
extern uint16_t Tempdata;

int main(void) {
	RCC_init();
	ADC_init();
	USART_init();
	
	while (1) {
		printf("Deep_ADC: %d\t", Deepdata);
		printf("Deepth: %.4fmm\t", (float)Deepdata / 650 * 4);
		
		printf("Temp_ADC: %d\t", Tempdata);
		printf("Temp: %.4f\t", ((V25 - Tempdata) / AVG_SLOPE) + 25);
		
		printf("\n");
	}
}
