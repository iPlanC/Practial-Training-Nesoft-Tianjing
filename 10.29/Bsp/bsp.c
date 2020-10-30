#include "bsp.h"

/*
 * 函数名：BSP_Init
 * 描述  ：时钟初始化、硬件初始化
 * 输入  ：无
 * 输出  ：无
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
 * 函数名：SysTick_init
 * 描述  ：配置SysTick定时器
 * 输入  ：无
 * 输出  ：无
 */
void SysTick_init(void)
{
	while (SysTick_Config(72));
	SysTick->CTRL &= ~(1 << 0);
}


/* --------------------------------------end of file--------------------------------------- */
