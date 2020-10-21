#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#include <stm32f10x.h>
#include "Led_Key.h"

extern unsigned int high_value;
extern unsigned char high_complete_flag;
extern unsigned int peroid_times;

void TIM2_BaseConfiguration(void);
void TIM2_PWM_Configuration(void);
void TIM3_InputCaputure_Configuration(void);

void TIM4_PWM_Configuration(void);

#endif
