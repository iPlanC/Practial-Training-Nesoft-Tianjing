#ifndef __BSP_74HC595_H__
#define __BSP_74HC595_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"
#include "bsp_digital_tube.h"

void HC595_GPIO_Configuration(void);
void HC595_Send_Data(unsigned char num, unsigned char show_bit);
void display(unsigned int n);

#endif
