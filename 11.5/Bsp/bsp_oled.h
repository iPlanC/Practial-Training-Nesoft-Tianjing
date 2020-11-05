/*
	OLED0.96                  							STM32
	GND        				<----------->					GND
	VCC        				<----------->					3.3V
	D0(SCLK)         	<----------->					PA6			
	D1SDIN()         	<----------->					PA7
	RES        				<----------->					PA8
	DC(Data/Command)	<----------->					PA9
	CS								<----------->					PA10
*/


#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__

#include <stm32f10x.h>
//#include "bsp_SysTick.h"

//OLED¶Ë¿ÚÅäÖÃ
#define OLED_SCLK_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define OLED_SCLK_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_6)

#define OLED_SDIN_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define OLED_SDIN_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_7)

#define OLED_RST_Set() GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define OLED_RST_Clr() GPIO_ResetBits(GPIOA, GPIO_Pin_8)

#define OLED_DC_Set()		GPIO_SetBits(GPIOA, GPIO_Pin_9)
#define OLED_DC_Clr()		GPIO_ResetBits(GPIOA, GPIO_Pin_9)

#define OLED_CS_Set() 	GPIO_SetBits(GPIOA, GPIO_Pin_10)
#define OLED_CS_Clr() 	GPIO_ResetBits(GPIOA, GPIO_Pin_10)


#define OLED_CMD	0 //Ð´ÃüÁî
#define OLED_DATA	1 //Ð´Êý¾Ý

void Delay_us(unsigned int us);
void OLED_Init(void);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char bmp[]);


#endif
