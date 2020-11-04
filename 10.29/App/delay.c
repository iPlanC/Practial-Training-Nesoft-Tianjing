#include "delay.h"

unsigned int timer;

void delay_us(unsigned int us) {
	timer = us;
	SysTick->CTRL |= (1 << 0);
	while (timer);
	SysTick->CTRL &= ~(1 << 0);
}

void delay_ms(unsigned int ms) {
	while (ms--) {
		delay_us(1000);
	}
}