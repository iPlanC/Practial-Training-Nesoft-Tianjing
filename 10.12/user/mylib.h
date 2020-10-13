#ifndef __MYLIB_H__
#define __MYLIB_H__

#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>

//#define USE_WWDG
//#define USE_USART2
#define USE_AFIO
#define USE_GPIOA
//#define USE_GPIOB
#define USE_USART1
#define USE_ADC1
#define USE_DMA

#define KEY_OFF           0
#define KEY_ON            1
#define KEY_LONG          2
#define LED_TOGGLE        (GPIOA->ODR ^= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)
#define LED_TOGGLE1       (GPIOA->ODR ^= GPIO_Pin_1)
#define LED_TOGGLE2       (GPIOA->ODR ^= GPIO_Pin_2)
#define LED_TOGGLE3       (GPIOA->ODR ^= GPIO_Pin_3)
#define LED_TOGGLE4       (GPIOA->ODR ^= GPIO_Pin_4)
#define BEEP_TOGGLE       (GPIOB->ODR ^= GPIO_Pin_8)

void delayus              (unsigned int us);

void GPIO_init            (GPIO_TypeDef* GPIOx, u16 GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed, GPIOMode_TypeDef GPIO_Mode);
void LED_init             (void);
void RCC_init             (void);
void KEY_init             (void);
void PIR_init             (void);
void BEEP_init            (void);
void RELAY_init           (void);
void MQ_init              (void);
void SysTick_init         (void);
void ADC_init             (void);
void USART_init           (void);

int KEY_Scan              (GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x);
int PIR_Scan              (GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x);
int MQ_Scan               (GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x);

#endif
