#include "app.h"

/* 
* ��������Task_LED
* ����  : LED��ˮ��	
* ����  ����
* ���  : ��
*/
void Task_LED1(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void Task_LED2(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void Task_LED3(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void Task_LED4(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;                		// 'p_arg' ��û���õ�����ֹ��������ʾ����

	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
		OSTimeDlyHMSM(0, 0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}
