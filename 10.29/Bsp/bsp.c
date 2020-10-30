#include "bsp.h"

/*
 * ��������BSP_Init
 * ����  ��ʱ�ӳ�ʼ����Ӳ����ʼ��
 * ����  ����
 * ���  ����
 */
void BSP_Init(void)
{
	SysTick_init();
	
	OLED_Init();
	Motor_Configuration();
	//Key_Configuration();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

/*
 * ��������SysTick_init
 * ����  ������SysTick��ʱ��
 * ����  ����
 * ���  ����
 */
void SysTick_init(void)
{
	while (SysTick_Config(72));
	SysTick->CTRL &= ~(1 << 0);
}


/* --------------------------------------end of file--------------------------------------- */
