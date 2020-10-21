#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include <stm32f10x.h>
#include <stdio.h>
#include "bsp_iic_at24c02.h"

void Uart1_Configuration(void);
void Uart1_NVIC_Init(void);
void USART_SendString(const unsigned char *pt);
void Uart1_scanf(unsigned int *pt, unsigned int bits);

#endif
