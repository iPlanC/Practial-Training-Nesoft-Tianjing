#define GPIOA_CRL (*(volatile unsigned long*)0x40010800)
#define GPIOA_ODR (*(volatile unsigned long*)0x4001080c)

int main() {
	// GPIOA = 0x4001 0800
	// GPIOA_CRL [19, 4] = 0011 0011 0011 0011 = 0x00033330
	// unsigned long *gpioa_crl = (unsigned long *)0x40010800;
	
	// *gpio_a &= 0xFFF0000F;
	GPIOA_CRL &= ~((0xF<<16) | (0xF<<12) | (0xF<<8) | (0xF<<4));
	// *gpio_a |= 0x00033330;
	GPIOA_CRL |= (0x3<<16) | (0x3<<12) | (0x3<<8) | (0x3<<4);
	// set PA1 PA2 PA3 PA4 into push-pull output @ 50MHz
	
	while (1) {
		// GPIO_SetBits(GPIOx, GPIO_Pin_x);
		// GPIO_SetBits(GPIOA, GPIO_Pin_1);
		// GPIO_SetBits(GPIOA, GPIO_Pin_2);
		// GPIO_SetBits(GPIOA, GPIO_Pin_3);
		// GPIO_SetBits(GPIOA, GPIO_Pin_4);
		
		// unsigned long *gpioa_odr= (unsigned long *)0x4001080C;
		// *gpioa_odr &= 0x0000FF00;
		GPIOA_ODR &= (0xF<<12) | (0xF<<8);
		// *gpioa_odr |= 0x0000001E;
		GPIOA_ODR |= (0x1<<4) | (0xE<<0);
	}
}
