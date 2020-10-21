#ifndef __BSP_LCD1602_H__
#define __BSP_LCD1602_H__

#include <stm32f10x.h>
#include "bsp_SysTick.h"

/*	LCD1602管脚定义    
	1.LCD1602_VSS------------- GND
	2.LCD1602_VCC------------- 3.3V
	3.LCD1602_VEE------------- 通过电位器接地
	4.LCD602_RS		------------ PA5
	5.LCD602_R/W ------------- PB12
	6.LCD1602_E  ------------- PB13
	7.LCD1602_DB0 ------------ PB14
	8.LCD1602_DB1 ------------ PB15
	9.LCD1602_DB2 ------------ PA9
	10.LCD1602_DB3 ----------- PA10
	11.LCD1602_DB4 ----------- PA11
	12.LCD1602_DB5 ----------- PA12
	13.LCD1602_DB6 ----------- PB5
	14.LCD1602_DB7 ----------- PC13
	15.LCD1602_A   ----------- 3.3V
	16.LCD1602_K   ----------- GND
*/

#define LCD1602_RS_Set()	GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define LCD1602_RS_Clr()	GPIO_ResetBits(GPIOA, GPIO_Pin_5)

#define LCD1602_RW_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define LCD1602_RW_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_12)

#define LCD1602_EN_Set()	GPIO_SetBits(GPIOB, GPIO_Pin_13)
#define LCD1602_EN_Clr()	GPIO_ResetBits(GPIOB, GPIO_Pin_13)

#define SET_LCD1602_D0(a)	GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(a))
#define SET_LCD1602_D1(a)	GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)(a))
#define SET_LCD1602_D2(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_9, (BitAction)(a))
#define SET_LCD1602_D3(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction)(a))
#define SET_LCD1602_D4(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_11, (BitAction)(a))
#define SET_LCD1602_D5(a)	GPIO_WriteBit(GPIOA, GPIO_Pin_12, (BitAction)(a))
#define SET_LCD1602_D6(a)	GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)(a))
#define SET_LCD1602_D7(a)	GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(a))

void LCD1602_GPIO_Configuration(void);
void LCD1602_Init(void);
void LCD1602_Clear_Screen(void);
void LCD1602_Write_Cmd(unsigned char cmd);
void LCD1602_Show_Str(unsigned char x, unsigned char y, unsigned char *str);
void LCD1602_Show_Char(unsigned char x, unsigned char y, unsigned char dat);


#endif
