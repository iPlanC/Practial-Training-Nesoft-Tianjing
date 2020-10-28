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

extern OS_SEM  SEM1;
extern OS_TMR  tmr;
extern OS_TCB  LED_TCB;
extern OS_TCB  LED1_TCB;
extern OS_TCB  LED2_TCB;
extern OS_TCB  LED3_TCB;
extern OS_TCB  LED4_TCB;

void TimCallback (OS_TMR *p_tmr, void *p_arg) {
	p_arg = p_arg;
	LED_TOGGLE;
}

void Task1(void *p_arg) {
	OS_ERR err;
	char tsk1_str[] = "Hello World\n";
	while (1) {
		OSSemPend(&SEM1, 0, OS_OPT_PEND_BLOCKING, (void *)0, &err);
		memset(str, '\0', sizeof(str));
		memcpy(str, tsk1_str, sizeof(tsk1_str));
		printf("%s", str);
		OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT,&err);
		OSSemPost(&SEM1, OS_OPT_POST_ALL, &err);
	}
}

void Task2(void *p_arg) {
	OS_ERR err;
	char tsk2_str[] = "Morning\n";
	while (1) {
		OSSemPend(&SEM1, 0, OS_OPT_PEND_BLOCKING, (void *)0, &err);
		memset(str, '\0', sizeof(str));
		memcpy(str, tsk2_str, sizeof(tsk2_str));
		printf("%s", str);
		OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT,&err);
		OSSemPost(&SEM1, OS_OPT_POST_ALL, &err);
	}
}

void Task_LED1(void *p_arg)
{
	int i = 0;
	int j = 0;
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	while (1)
	{
		for (i = 0; i < 10; i++) {
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
			GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		}
	}
}

void Task_LED2(void *p_arg)
{
	int i = 0;
	int j = 0;
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	while (1)
	{
		for (i = 0; i < 10; i++) {
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
			GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		}
	}
}

void Task_LED3(void *p_arg)
{
	int i = 0;
	int j = 0;
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	while (1)
	{
		for (i = 0; i < 10; i++) {
			GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
			GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		}
	}
}

void Task_LED4(void *p_arg)
{
	int i = 0;
	int j = 0;
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' 并没有用到，防止编译器提示警告

	while (1)
	{
		for (i = 0; i < 10; i++) {
			GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
			GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
			for (j = 0; j < 0x5FFFF; j++);
			//OSTimeDlyHMSM(0, 0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		}
	}
}

int fputc (int c, FILE *fp)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
	
	return 0;
}
