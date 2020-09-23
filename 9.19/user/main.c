#include "main.h"

void delay(unsigned int loop) {
	while (loop--);
}

int main() {
	RCC->APB2ENR |= (0x1 << 2);
	GPIOA->CRL &= ~((0xF  <<  16) | (0xF << 12) | (0xF << 8) | (0xF << 4));
	GPIOA->CRL |= (0x3 << 16) | (0x3 << 12) | (0x3 << 8) | (0x3 << 4);
	// set PA1 PA2 PA3 PA4 into push-pull output @ 50MHz
	
	GPIOA->ODR &= ~((0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1));
	while (1) {
		// GPIOA->ODR &= ~((0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1));
		// delay(0x5FFFF);
		// GPIOA->ODR |= (0x1 << 4) | (0x1 << 3) | (0x1 << 2) | (0x1 << 1);
		// delay(0x5FFFF);
		GPIOA->ODR |= (0x1 << 1);
		delay(0xFFFFF);
		GPIOA->ODR &= ~((0x1 << 1));
		
		GPIOA->ODR |= (0x1 << 2);
		delay(0xFFFFF);
		GPIOA->ODR &= ~((0x1 << 2));
		
		GPIOA->ODR |= (0x1 << 3);
		delay(0xFFFFF);
		GPIOA->ODR &= ~((0x1 << 3));
		
		GPIOA->ODR |= (0x1 << 4);
		delay(0xFFFFF);
		GPIOA->ODR &= ~((0x1 << 4));
	}
}
