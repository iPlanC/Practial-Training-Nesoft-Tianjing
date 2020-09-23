#ifndef __LED_KEY_H__
#define __LED_KEY_H__

#include <stm32f10x.h>

#define KEY_ON	1
#define KEY_OFF	0

void delay(unsigned int loop);
void LED_init(void);
void RCC_init(void);
int KEY_Scan(GPIO_TypeDef* GPIOx, u16 GIO_Pin);

#endif
