#ifndef __MYLIB_H__
#define __MYLIB_H__

#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//#define USE_WWDG
//#define USE_USART2
//#define USE_RTC
#define USE_TIM2
//#define USE_AFIO
#define USE_GPIOA
//#define USE_GPIOB
//#define USE_USART1
//#define USE_ADC1
//#define USE_DMA

#define KEY_OFF           0
#define KEY_ON            1
#define KEY_LONG          2
#define LED_TOGGLE        (GPIOA->ODR ^= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)
#define LED_TOGGLE1       (GPIOA->ODR ^= GPIO_Pin_1)
#define LED_TOGGLE2       (GPIOA->ODR ^= GPIO_Pin_2)
#define LED_TOGGLE3       (GPIOA->ODR ^= GPIO_Pin_3)
#define LED_TOGGLE4       (GPIOA->ODR ^= GPIO_Pin_4)
#define BEEP_TOGGLE       (GPIOB->ODR ^= GPIO_Pin_8)

#define leapDay(year)     (isLeap(year) ? 366 : 365)

typedef struct {
	unsigned int year;
	unsigned int month;
	unsigned int day;
} dateTime;

void delayus              (unsigned int us);

void GPIO_init            (GPIO_TypeDef* GPIOx, u16 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode);
void LED_init             (void);
void RCC_init             (void);
void TIM_init             (void);
void SysTick_init         (void);

#endif
