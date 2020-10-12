#ifndef __MYLIB_H__
#define __MYLIB_H__

#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>

#define KEY_OFF           0
#define KEY_ON            1
#define KEY_LONG          2
#define LED_TOGGLE        (GPIOA->ODR ^= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)
#define LED_TOGGLE1       (GPIOA->ODR ^= GPIO_Pin_1)
#define LED_TOGGLE2       (GPIOA->ODR ^= GPIO_Pin_2)
#define LED_TOGGLE3       (GPIOA->ODR ^= GPIO_Pin_3)
#define LED_TOGGLE4       (GPIOA->ODR ^= GPIO_Pin_4)
#define BEEP_TOGGLE       (GPIOB->ODR ^= GPIO_Pin_8)

void delay                (unsigned int us);
void LED_init             (void);
void RCC_init             (void);
void KEY_init             (void);
void PIR_init             (void);
void BEEP_init            (void);
void RELAY_init           (void);
void MQ_init              (void);
void EXTI_init            (void);
void SysTick_init         (void);
void IWDG_init            (void);
void USART_init           (void);
void USART_SendString     (USART_TypeDef* USARTx, char* str, int length);
void WWDG_init            (unsigned char counter, unsigned char value, unsigned int prescaler);
int KEY_Scan              (GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x);
int PIR_Scan              (GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x);
int MQ_Scan               (GPIO_TypeDef* GPIOx, u16 GPIO_Pin_x);

#endif
