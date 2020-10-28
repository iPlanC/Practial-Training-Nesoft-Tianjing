#include "app.h"
#include <stdio.h>
#include <string.h>

/* 
* 函数名：Task_LED
* 描述  : LED流水灯	
* 输入  ：无
* 输出  : 无
*/

int flag = 0;
char str[30];

extern OS_FLAG_GRP flags;

void Task1(void *p_arg) {
	OS_ERR err;
	while (1) {
		if (Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON) {
			
		}
		if (Key_Scan(GPIOA, GPIO_Pin_5) == KEY_ON) {
			
		}
		OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void Task2(void *p_arg) {
	OS_ERR err;
	while (1) {
		
		OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

int fputc (int c, FILE *fp)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	
	return 0;
}
