#ifndef __BSP_ULN2003_H__
#define __BSP_ULN2003_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"

#define STEPPER_ANGLE		0.703125

enum dir{Pos, Neg};   //Pos = 0, Neg = 1

#define IN1_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)
#define IN1_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)

#define IN2_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET)
#define IN2_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET)

#define IN3_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_SET)
#define IN3_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_6, Bit_RESET)

#define IN4_HIGH	GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_SET)
#define IN4_LOW		GPIO_WriteBit(GPIOA, GPIO_Pin_7, Bit_RESET)

void ULN2003_Configuration(void);
void stepper(unsigned int dir, unsigned int speed);
void angle_control(unsigned int dir, double angle, unsigned int speed);

#endif
