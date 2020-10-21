#ifndef __BSP_TCS3200_H__
#define __BSP_TCS3200_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"
#include <stdio.h>

void TCS3200_Configuration(unsigned int s0, unsigned int s1);
void PA4_EXTI4_Configuration(void);
void White_Balance(void);
unsigned int tcs3200_red(void);
unsigned int tcs3200_green(void);
unsigned int tcs3200_blue(void);

#endif
